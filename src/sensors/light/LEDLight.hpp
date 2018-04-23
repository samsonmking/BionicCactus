#ifndef LED_LIGHT_H
#define LED_LIGHT_H

#include "Light.hpp"
#include "time/Clock.hpp"
#include <Arduino.h>

using namespace Time;

namespace Sensors {
  namespace Light {

    class LEDLight : public Light {
    public:
      LEDLight(Clock& clock, int lightPin);
      virtual void setTimeOn(const char* timeOn) override;
      virtual const char* getTimeOn() override;
      virtual void setTimeOff(const char* timeOff) override;
      virtual const char* getTimeOff() override;
      inline void setBrightness(int brightness) {
        _brightness = brightness;
      };
      virtual int getBrightness() override;
      virtual void loop() override;
      virtual bool isOn() {
        return _lastOutput > 0;
      };
      int getLastOutput() {
        return _lastOutput;
      };
    private:
      int _lightPin;
      int _brightness;
      int _lastOutput = 0;
      Clock _clock;
      char _timeOn[9];
      char _timeOff[9];
    };

  }
}

#endif
