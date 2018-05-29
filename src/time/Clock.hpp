#ifndef CLOCK_H
#define CLOCK_H

#include "TimeProvider.hpp"
#include <Arduino.h>

namespace Time {

  class Clock {
  public:
    Clock(TimeProvider& timeProvider, int timeZone);
    bool isAtOrPastTime(const char* timeChr);
    Time::time_t getTimeFromChr(char* input);
    Time::time_t getCurrentTime();
    void getTimeChr(char* out, time_t moment);
    void getTimeNowChr(char* out);
    unsigned int getSecondsSinceMidnight(time_t time);
    unsigned int getSecondsSinceMidnight(const char* timeChr);
  private:
    int _timeZone;
    TimeProvider& _timeProvider;
    int hour(time_t aTime);
    int minute(time_t aTime);
    int second(time_t aTime);
    void printDigits(char* out, int digits);
  };
  
}

#endif
