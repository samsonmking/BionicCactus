#ifdef UNIT_TEST

#include <Arduino.h>
#include <unity.h>
#include <MockTimeProvider.hpp>
#include <Clock.hpp>

void test_mock_provider() {
  // 10/24/2017 11:50:15 PM GMT
  time_t testTime = 1508889015;
  MockTime mocktime(testTime);
  time_t currentTime = mocktime.getCurrentTime();
  TEST_ASSERT_EQUAL(testTime, currentTime);
}

void test_get_current_time() {
  // 10/24/2017 11:50:15 PM GMT
  time_t testTime = 1508889015;
  MockTime mocktime(testTime);
  Clock aclock(&mocktime, 0);
  time_t currentTime = aclock.getCurrentTime();
  TEST_ASSERT_EQUAL(testTime, currentTime);
}

void test_get_time_now_chr() {
  // 10/24/2017 11:50:15 PM GMT
  time_t testTime = 1508889015;
  MockTime mocktime(testTime);
  Clock aclock(&mocktime, 0);
  char timeNow[9];
  aclock.getTimeNowChr(timeNow);
  const char* correctTime = "23:50:15";
  TEST_ASSERT_EQUAL_STRING(correctTime, timeNow);
}

void test_get_time_now_chr_est() {
  // 10/24/2017 11:50:15 PM GMT
  time_t testTime = 1508889015;
  MockTime mocktime(testTime);
  Clock aclock(&mocktime, -4);
  char timeNow[9];
  aclock.getTimeNowChr(timeNow);
  const char* correctTime = "19:50:15";
  TEST_ASSERT_EQUAL_STRING(correctTime, timeNow);
}

void test_past_time() {
  // 10/24/2017 11:50:15 PM GMT
  time_t testTime = 1508889015;
  MockTime mocktime(testTime);
  Clock aclock(&mocktime, -4);
  TEST_ASSERT_TRUE(aclock.isAtOrPastTime("19:48:00"));
}

void test_not_past_time() {
  // 10/24/2017 11:50:15 PM GMT
  time_t testTime = 1508889015;
  MockTime mocktime(testTime);
  Clock aclock(&mocktime, -4);
  TEST_ASSERT_FALSE(aclock.isAtOrPastTime("19:51:00"));
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

    UNITY_END();
}

void loop() {

}

#endif
