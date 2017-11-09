#ifndef LED_LIGHT_H
#define LED_LIGHT_H

#include <Light.hpp>
#include <Clock.hpp>
#include <Arduino.h>

class LEDLight : public Light {
public:
  LEDLight(Clock& clock, int lightPin);
  void setTimeOn(const char* timeOn);
  void setTimeOff(const char* timeOff);
  void setBrightness(int brightness) {
    _brightness = brightness;
  };
  virtual void loop();
  const char* getTimeOn();
  const char* getTimeOff();
  virtual bool isOn() {
    return _lastOutput > 0;
  };
  int getLastOutput() {
    return _lastOutput;
  };
private:
  int _lightPin;
  int _brightness = 100;
  int _lastOutput = 0;
  Clock _clock;
  char _timeOn[9];
  char _timeOff[9];
};

#endif
