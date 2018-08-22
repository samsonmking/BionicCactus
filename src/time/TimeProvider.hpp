#ifndef TIMEPROVIDER_H
#define TIMEPROVIDER_H

namespace Time {

  typedef unsigned long unix_time_t;

  class TimeProvider {
  public:
    virtual unix_time_t getCurrentTime() = 0;
  };

}

#endif
