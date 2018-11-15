#ifndef MOCK_SENSOR_H
#define MOCK_SENSOR_H

#include "SoilSensor.hpp"

namespace Sensors {
  namespace Soil {

    class MockSoilSensor : public SoilSensor {
      public:
        MockSoilSensor(int p) : percent(p), 
        _high(1000), 
        _low(500) {

        };
        int percent;
        int getPercent() {
          return percent;
        };
        int getRaw() override {
            return 1234;
        }
        void setHigh(int high) override {
            _high = high;
        }
        int getHigh() override {
            return _high;
        }
        void setLow(int low) override {
            _low = low;
        }
        int getLow() override {
            return _low;
        }
        void loop() override {
        }
      private:
        int _low;
        int _high;
    };

  }
}

#endif
