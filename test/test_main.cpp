#ifdef UNIT_TEST

#include <Arduino.h>
#include "unity.h"
#include "time/Clock.hpp"
#include "time/MockTimeProvider.hpp"
#include "MockMillisProvider.hpp"
#include "sensors/light/LEDLight.hpp"
#include "sensors/light/LEDLight.cpp"
#include "sensors/soil/DFSoil.hpp"
#include "sensors/soil/MockSoilSensor.hpp"
#include "sensors/pump/MockPump.hpp"
#include "SoilRunLoop.hpp"
#include "email/SMTPUtils.hpp"

// The linker is not automatically including the implementations so they must be manually loaded.
// This problem should be resolved after refacting classes into the lib folder to conform with
// Arduino standard. This is a workaround to ensure tests continue working until then.
#include "time/Clock.cpp"
#include "sensors/soil/DFSoil.cpp"
#include "time/Timer.cpp"
#include "time/TimeUnitConverter.cpp"
#include "SoilRunLoop.cpp"
#include "email/SMTPUtils.cpp"

using namespace Email;

Time::unix_time_t testTime = 1508889015;
Time::MockTime mocktime(testTime);
Clock aclock(mocktime, 1);

// Clock Tests
void test_mock_provider() {
  // 10/24/2017 11:50:15 PM GMT
  unix_time_t testTime = 1508889015;
  MockTime mocktime(testTime);
  unix_time_t currentTime = mocktime.getCurrentTime();
  TEST_ASSERT_EQUAL(testTime, currentTime);
}

void test_get_current_time() {
  // 10/24/2017 11:50:15 PM GMT
  unix_time_t testTime = 1508889015;
  MockTime mocktime(testTime);
  int timeZone = 1;
  Clock aclock(mocktime, timeZone);
  unix_time_t currentTime = aclock.getCurrentTime();
  TEST_ASSERT_EQUAL(testTime  + (timeZone * 3600), currentTime);
}

void test_get_time_now_chr() {
  // 10/24/2017 11:50:15 PM GMT
  unix_time_t testTime = 1508889015;
  MockTime mocktime(testTime);
  Clock aclock(mocktime, 0);
  char timeNow[9];
  aclock.getTimeNowChr(timeNow);
  const char* correctTime = "23:50:15";
  TEST_ASSERT_EQUAL_STRING(correctTime, timeNow);
}

void test_get_time_now_chr_est() {
  // 10/24/2017 11:50:15 PM GMT
  unix_time_t testTime = 1508889015;
  MockTime mocktime(testTime);
  Clock aclock(mocktime, -4);
  char timeNow[9];
  aclock.getTimeNowChr(timeNow);
  const char* correctTime = "19:50:15";
  TEST_ASSERT_EQUAL_STRING(correctTime, timeNow);
}

void test_past_time() {
  // 10/25/2017 1:00:00 PM GMT
  unix_time_t testTime = 1508936400;
  MockTime mocktime(testTime);
  Clock aclock(mocktime, 0);
  TEST_ASSERT_TRUE(aclock.isAtOrPastTime("9:00:00"));
}

void test_not_past_time() {
  // 10/25/2017 1:00:00 PM GMT
  unix_time_t testTime = 1508936400;
  MockTime mocktime(testTime);
  Clock aclock(mocktime, 0);
  TEST_ASSERT_FALSE(aclock.isAtOrPastTime("14:00:00"));
}

// Light Tests
void test_light_on_after_settime() {
  //10/25/2017 1:00:00 PM GMT
  unix_time_t testTime = 1508936400;
  MockTime mocktime(testTime);
  Clock aclock(mocktime, 0);
  LEDLight alight(aclock, D5);
  alight.setTimeOn("09:00:00");
  alight.setTimeOff("14:00:00");
  alight.loop();
  TEST_ASSERT_EQUAL(PWMRANGE, alight.getLastOutput());
}

void test_light_on_after_settime_half_bright() {
  //10/25/2017 1:00:00 PM GMT
  unix_time_t testTime = 1508936400;
  MockTime mocktime(testTime);
  Clock aclock(mocktime, 0);
  LEDLight alight(aclock, D5);
  alight.setTimeOn("09:00:00");
  alight.setTimeOff("14:00:00");
  alight.setBrightness(50);
  alight.loop();
  TEST_ASSERT_EQUAL(PWMRANGE / 2, alight.getLastOutput());
}

void test_light_off_after_settime() {
  //10/25/2017 1:00:00 PM GMT
  unix_time_t testTime = 1508936400;
  MockTime mocktime(testTime);
  Clock aclock(mocktime, 0);
  LEDLight alight(aclock, D5);
  alight.setTimeOn("09:00:00");
  alight.setTimeOff("11:00:00");
  alight.loop();
  TEST_ASSERT_EQUAL(0, alight.getLastOutput());
}

// DFSoil Tests
void test_calculate_percent() {
  MockMillisProvider aMillis(0);
  DFSoil dfsoil(A0, aMillis);
  dfsoil.setLow(770);
  dfsoil.setHigh(419);
  int percent = dfsoil.calculatePercent(500);
  TEST_ASSERT_EQUAL(76, percent);
}

// SoilRunLoop Tests
void test_starting_state_check_moisture() {
  MockMillisProvider mocktime(0);
  MockPump pump;
  MockSoilSensor sensor(75);
  SoilRunLoop runLoop(&pump, sensor, mocktime);
  TEST_ASSERT_EQUAL(SoilRunLoop::CheckMoisture, runLoop.getState());
}

void test_pump_vol() {
  MockMillisProvider mocktime(0);
  MockPump pump;
  MockSoilSensor sensor(50);
  SoilRunLoop runLoop(&pump, sensor, mocktime);
  int disperseMin = 5;
  runLoop.setDispersionMin(disperseMin);
  runLoop.setmlPerPercent(1);
  runLoop.setSetPoint(80);
  mocktime.setMillis(convertMillis(disperseMin + 1, Units::MINUTES));
  runLoop.loop();
   TEST_ASSERT_EQUAL(SoilRunLoop::CheckMoisture, runLoop.getState());
  runLoop.loop();
  TEST_ASSERT_EQUAL(SoilRunLoop::Pumping, runLoop.getState());
  TEST_ASSERT_EQUAL(30, pump.lastVol);
}

void test_full_cycle() {
  MockMillisProvider mocktime(0);
  MockPump pump;
  MockSoilSensor sensor(50);
  SoilRunLoop runLoop(&pump, sensor, mocktime);
  int disperseMin = 5;
  runLoop.setDispersionMin(disperseMin);
  runLoop.setmlPerPercent(1);
  runLoop.setSetPoint(80);
  runLoop.setHrsAtMoisture(12);
  runLoop.setHrsDry(12);
  mocktime.setMillis(convertMillis(disperseMin + 1, Units::MINUTES));
  TEST_ASSERT_EQUAL(SoilRunLoop::Dispersing, runLoop.getState());
  runLoop.loop();
  TEST_ASSERT_EQUAL(SoilRunLoop::CheckMoisture, runLoop.getState());
  runLoop.loop();
  TEST_ASSERT_EQUAL(SoilRunLoop::Pumping, runLoop.getState());
  TEST_ASSERT_EQUAL(30, pump.lastVol);
  pump.dispenseIsDone = true;
  runLoop.loop();
  TEST_ASSERT_EQUAL(SoilRunLoop::Dispersing, runLoop.getState());
  mocktime.setMillis(convertMillis((disperseMin * 2) + 1, Units::MINUTES));
  sensor.percent = 80;
  runLoop.loop();
  TEST_ASSERT_EQUAL(SoilRunLoop::CheckMoisture, runLoop.getState());
  mocktime.setMillis(convertMillis(13, Units::HOURS));
  runLoop.loop();
  TEST_ASSERT_EQUAL(SoilRunLoop::Drying, runLoop.getState());
  mocktime.setMillis(convertMillis(25, Units::HOURS));
  runLoop.loop();
  TEST_ASSERT_EQUAL(SoilRunLoop::CheckMoisture, runLoop.getState());
}

void test_disabled() {
  MockMillisProvider mocktime(0);
  MockPump pump;
  MockSoilSensor sensor(50);
  SoilRunLoop runLoop(&pump, sensor, mocktime);
  int disperseMin = 5;
  runLoop.setDispersionMin(disperseMin);
  runLoop.setmlPerPercent(1);
  runLoop.setSetPoint(80);
  runLoop.setHrsAtMoisture(12);
  runLoop.setHrsDry(12);
  mocktime.setMillis(convertMillis(disperseMin + 1, Units::MINUTES));
  runLoop.loop();
  TEST_ASSERT_EQUAL(SoilRunLoop::CheckMoisture, runLoop.getState());
  runLoop.setEnabled(false);
  TEST_ASSERT_FALSE(runLoop.getEnabled());
  runLoop.loop();
  TEST_ASSERT_EQUAL(SoilRunLoop::Disabled, runLoop.getState());
  runLoop.setEnabled(true);
  TEST_ASSERT_TRUE(runLoop.getEnabled());
  runLoop.loop();
  TEST_ASSERT_EQUAL(SoilRunLoop::Dispersing, runLoop.getState());
}


// Email Tests
void test_email_status_code() {
  const char* example_reply_with_code = "220 smtp.example.com ESMTP Postfix";
  int good_code = getStatusCodeFromReply((uint8_t*)example_reply_with_code);
  TEST_ASSERT_EQUAL(220, good_code);
  const char* example_reply_no_code = "no code here";
  int bad_code = getStatusCodeFromReply((uint8_t*)example_reply_no_code);
  TEST_ASSERT_EQUAL(-1, bad_code);
  const char* too_short = "22";
  int short_code = getStatusCodeFromReply((uint8_t*)too_short);
  TEST_ASSERT_EQUAL(-1, short_code);
}

void setup() {
    delay(2000);

    UNITY_BEGIN();

    // Clock Tests
    RUN_TEST(test_mock_provider);
    RUN_TEST(test_get_current_time);
    RUN_TEST(test_get_time_now_chr);
    RUN_TEST(test_get_time_now_chr_est);
    RUN_TEST(test_past_time);
    RUN_TEST(test_not_past_time);

    // Light Tests
    RUN_TEST(test_light_on_after_settime);
    RUN_TEST(test_light_on_after_settime_half_bright);
    RUN_TEST(test_light_off_after_settime);

    // DFSoil Tests
    RUN_TEST(test_calculate_percent);

    // SoilRunLoop Tests
    RUN_TEST(test_pump_vol);
    RUN_TEST(test_full_cycle);
    RUN_TEST(test_disabled);

    // Email Tests
    RUN_TEST(test_email_status_code);

    UNITY_END();
}

void loop() {

}

#endif
