#ifndef LIGHT_H
#define LIGHT_H

#include <Clock.hpp>
#include <Arduino.h>

class Light {
public:
  Light(int lightPin);
  void setTimeOn(const char* timeOn);
  void setTimeOff(const char* timeOff);
  void loop();
  const char* getTimeOn();
  const char* getTimeOff();
private:
  int _lightPin;
  Clock* _clock;
  char _timeOn[9];
  char _timeOff[9];
};

#endif
