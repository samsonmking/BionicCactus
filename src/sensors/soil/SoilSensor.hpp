#ifndef SOIL_SENSOR
#define SOIL_SENSOR

namespace Sensors {
  namespace Soil {

  class SoilSensor {
    public:
      virtual int getPercent() = 0;
    };

  }
}

#endif
