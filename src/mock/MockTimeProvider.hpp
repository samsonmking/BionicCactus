#ifndef MOCKTIME_H
#define MOCKTIME_H

#include <TimeLib.h>
#include <TimeProvider.hpp>

class MockTime : public TimeProvider {
public:
  MockTime(time_t time): currentTime(time) {
  };

  virtual time_t getCurrentTime() {
    return currentTime;
  }
  time_t currentTime;
  unsigned long millis;
  virtual unsigned long getMillis() {
    return millis;
  }
};

#endif
