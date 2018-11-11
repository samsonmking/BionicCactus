#ifndef SOIL_SENSOR
#define SOIL_SENSOR

namespace Sensors {
  namespace Soil {

  class SoilSensor {
    public:
      virtual int getPercent() = 0;
      virtual void setHigh(int high) = 0;
      virtual int getHigh() = 0;
      virtual void setLow(int low) = 0;
      virtual int getLow() = 0;
      virtual void loop() = 0;
    };

  }
}

#endif
