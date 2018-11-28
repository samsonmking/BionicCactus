#include "LEDLight.hpp"

using namespace Sensors::Light;

LEDLight::LEDLight(Clock& clock, int lightPin): 
_enabled(true),
_clock(clock), 
_lightPin(lightPin), 
_brightness(100),
_timeOn{'0','9',':','0','0',':','0','0'},
_timeOff{'1','7',':','0','0',':','0','0'},
_lastOutput(0) {
  analogWrite(_lightPin, _lastOutput);
}

void LEDLight::setEnabled(bool enabled) {
  _enabled = enabled;
  if(!_enabled) {
    _lastOutput = 0;
    analogWrite(_lightPin, _lastOutput);
  }
}

bool LEDLight::getEnabled() {
  return _enabled;
}

int LEDLight::getBrightness() {
  return _brightness;
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
    if (_enabled) {
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
}
