#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include <TimeLib.h>
#include <string.h>
#include <TimeProvider.hpp>

class Clock {
public:
  Clock(TimeProvider* timeProvider, int timeZone);
  unsigned long getMillis() {
    return _timeProvider->getMillis();
  };
  int timeZone;
  bool isAtOrPastTime(const char* timeChr);
  time_t getTimeFromChr(char* input);
  time_t getCurrentTime();
  void getTimeChr(char* out, time_t moment);
  void getTimeNowChr(char* out);
  unsigned int getSecondsSinceMidnight(time_t time);
  unsigned int getSecondsSinceMidnight(const char* timeChr);
private:
  TimeProvider* _timeProvider;
  void printDigits(char* out, int digits);
};

#endif
