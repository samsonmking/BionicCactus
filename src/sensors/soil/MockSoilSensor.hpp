#ifndef MOCK_SENSOR_H
#define MOCK_SENSOR_H

#include "SoilSensor.hpp"

namespace Sensors {
  namespace Soil {

    class MockSoilSensor : public SoilSensor {
      public:
        MockSoilSensor(int p) : percent(p)
        {

        };
        int percent;
        virtual int getPercent() {
          return percent;
        };
    };

  }
}

#endif
