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
      void setEnabled(bool enabled) override;
      bool getEnabled() override;
      void setTimeOn(const char* timeOn) override;
      const char* getTimeOn() override;
      void setTimeOff(const char* timeOff) override;
      const char* getTimeOff() override;
      inline void setBrightness(int brightness) {
        _brightness = brightness;
      };
      int getBrightness() override;
      void loop() override;
      bool isOn() {
        return _lastOutput > 0;
      };
      int getLastOutput() {
        return _lastOutput;
      };
    private:
      bool _enabled;
      int _lightPin;
      int _brightness;
      int _lastOutput = 0;
      Clock &_clock;
      char _timeOn[9];
      char _timeOff[9];
    };

  }
}

#endif
