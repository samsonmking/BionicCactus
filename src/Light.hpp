#ifndef LIGHT_H
#define LIGHT_H

#include <Clock.hpp>
#include <Arduino.h>

class Light {
public:
  Light(Clock& clock, int lightPin);
  void setTimeOn(const char* timeOn);
  void setTimeOff(const char* timeOff);
  void setBrightness(int brightness) {
    _brightness = brightness;
  }
  void loop();
  const char* getTimeOn();
  const char* getTimeOff();
  int getLastOutput() {
    return _lastOutput;
  }
private:
  int _lightPin;
  int _brightness = 100;
  int _lastOutput = 0;
  Clock _clock;
  char _timeOn[9];
  char _timeOff[9];
};

#endif
