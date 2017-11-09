#ifndef TIMEPROVIDER_H
#define TIMEPROVIDER_H

#include <TimeLib.h>

class TimeProvider {
public:
  virtual time_t getCurrentTime() = 0;
  virtual unsigned long getMillis() = 0;
};

#endif
