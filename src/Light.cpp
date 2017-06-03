#include <Light.hpp>

Light::Light(int lightPin) {
  _lightPin = lightPin;
  _clock = Clock::getInstance();
  pinMode(_lightPin, OUTPUT);
  digitalWrite(_lightPin, LOW);
}

void Light::setTimeOn(const char* timeOn)
{
  strcpy(_timeOn, timeOn);
}

void Light::setTimeOff(const char* timeOff)
{
  strcpy(_timeOff, timeOff);
}

const char* Light::getTimeOn() {
  return _timeOn;
}

const char* Light::getTimeOff() {
  return _timeOff;
}

void Light::loop() {
  bool pastOnTime = _clock->isATOrPastTime(_timeOn);
  bool pastOffTime = _clock->isATOrPastTime(_timeOff);
  if (pastOnTime && !pastOffTime) {
    digitalWrite(_lightPin, HIGH);
  }
  else {
    digitalWrite(_lightPin, LOW);
  }
}
