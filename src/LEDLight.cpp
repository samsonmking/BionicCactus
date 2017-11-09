#include <LEDLight.hpp>

LEDLight::LEDLight(Clock& clock, int lightPin): _clock(clock), _lightPin(lightPin) {
  _lastOutput = 0;
  analogWrite(_lightPin, _lastOutput);
}

void LEDLight::setTimeOn(const char* timeOn)
{
  strcpy(_timeOn, timeOn);
}

void LEDLight::setTimeOff(const char* timeOff)
{
  strcpy(_timeOff, timeOff);
}

const char* LEDLight::getTimeOn() {
  return _timeOn;
}

const char* LEDLight::getTimeOff() {
  return _timeOff;
}

void LEDLight::loop() {
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
