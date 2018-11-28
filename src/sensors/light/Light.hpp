#ifndef LIGHT_H
#define LIGHT_H

namespace Sensors {
  namespace Light {

    class Light {
      public:
        virtual void setEnabled(bool enabled) = 0;
        virtual bool getEnabled() = 0;
        virtual void setTimeOn(const char *timeOn) = 0;
        virtual const char *getTimeOn() = 0;
        virtual void setTimeOff(const char *timeOff) = 0;
        virtual const char *getTimeOff() = 0;
        virtual void setBrightness(int brightness) = 0;
        virtual int getBrightness() = 0;
        virtual void loop() = 0;
        virtual bool isOn() = 0;
      };
      
  }
}

#endif
