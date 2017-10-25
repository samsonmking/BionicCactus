#include <Light.hpp>

Light::Light(Clock& clock, int lightPin): _clock(clock), _lightPin(lightPin) {
  _lastOutput = 0;
  analogWrite(_lightPin, _lastOutput);
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
  bool pastOnTime = _clock.isAtOrPastTime(_timeOn);
  bool pastOffTime = _clock.isAtOrPastTime(_timeOff);
  if (pastOnTime && !pastOffTime) {
    _lastOutput = (_brightness * PWMRANGE) / 100;
    analogWrite(_lightPin, _lastOutput);
  }
  else {
    _lastOutput = 0;
    analogWrite(_lightPin, _lastOutput);
  }
}
