#pragma once

#include "TimeProvider.hpp"
#include <Arduino.h>

  class Clock {
    private:
    Time::TimeProvider& _timeProvider;
    int _timeZone;
    int hour(Time::unix_time_t aTime);
    int minute(Time::unix_time_t aTime);
    int second(Time::unix_time_t aTime);
    void printDigits(char* out, int digits);
    
  public:
    Clock(Time::TimeProvider& timeProvider, int timeZone);
    
    bool isAtOrPastTime(const char* timeChr);
    Time::unix_time_t getTimeFromChr(char* input);
    Time::unix_time_t getCurrentTime();
    void getTimeChr(char* out, Time::unix_time_t moment);
    void getTimeNowChr(char* out);
    unsigned int getSecondsSinceMidnight(Time::unix_time_t time);
    unsigned int getSecondsSinceMidnight(const char* timeChr);

  };

