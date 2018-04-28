#ifndef DFSOIL_H
#define DFSOIL_H

#include "SoilSensor.hpp"
#include "RunningMedian.h"
#include <Arduino.h>

namespace Sensors {
  namespace Soil {

    class DFSoil : public SoilSensor {
    public:
      DFSoil(int pin);
      int getPercent();
      void setHigh(int high) {
        _high = high;
        calculateConstants();
      };
      int getHigh() {
        return _high;
      }
      void setLow(int low) {
        _low = low;
        calculateConstants();
      };
      int getLow() {
        return _low;
      }
      int readRaw();
      virtual int readPercent();
      int calculatePercent(int raw);
    private:
      void calculateConstants();
      int _pin;
      int _high;
      int _low;
      float _m;
      float _b;
    };

  }
}

#endif
