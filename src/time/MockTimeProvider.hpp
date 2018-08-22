#ifndef MOCKTIME_H
#define MOCKTIME_H

#include "TimeProvider.hpp"
#include <Arduino.h>

namespace Time {

  class MockTime : public TimeProvider {
  public:
    MockTime(unix_time_t time): currentTime(time) {
    };

    virtual unix_time_t getCurrentTime() override {
      return currentTime;
    }
    unix_time_t currentTime;
  };

}

#endif
