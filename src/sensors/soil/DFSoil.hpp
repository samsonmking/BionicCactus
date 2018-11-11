#ifndef DFSOIL_H
#define DFSOIL_H

#include "SoilSensor.hpp"
#include "RunningMedian.h"
#include <Arduino.h>
#include "time/MillisProvider.hpp"
#include "time/Timer.hpp"
#include "CircularBuffer.h"

namespace Sensors {
  namespace Soil {

    class DFSoil : public SoilSensor {
    public:
      DFSoil(int pin, Time::MillisProvider& millisProvider);
      int getPercent() override;
      void setHigh(int high) override {
        _high = high;
        calculateConstants();
      };
      int getHigh() override {
        return _high;
      }
      void setLow(int low) override {
        _low = low;
        calculateConstants();
      };
      int getLow() override {
        return _low;
      }
      int readRaw();
      int readPercent();
      int calculatePercent(int raw);
      void loop() override;
    private:
      void calculateConstants();
      int _pin;
      Time::Timer _timer;
      int _high;
      int _low;
      float _m;
      float _b;
      CircularBuffer<int, 10> _buffer;
      int _lastAverage;
    };

  }
}

#endif
