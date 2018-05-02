#ifndef DFSOIL_H
#define DFSOIL_H

#include "SoilSensor.hpp"
#include "RunningMedian.h"
#include <Arduino.h>
#include "time/Clock.hpp"
#include "CircularBuffer.h"

namespace Sensors {
  namespace Soil {

    class DFSoil : public SoilSensor {
    public:
      DFSoil(int pin, Time::Clock &clock);
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
      void loop();
    private:
      void calculateConstants();
      int _pin;
      Time::Clock& _clock;
      int _high;
      int _low;
      float _m;
      float _b;
      CircularBuffer<int, 10> _buffer;
      int _lastAverage;
      unsigned long _lastRead;
    };

  }
}

#endif
