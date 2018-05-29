#ifndef TIMEPROVIDER_H
#define TIMEPROVIDER_H

namespace Time {

  typedef unsigned long time_t;

  class TimeProvider {
  public:
    virtual time_t getCurrentTime() = 0;
  };

}

#endif
