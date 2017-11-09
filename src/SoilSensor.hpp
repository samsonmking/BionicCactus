#ifndef SOIL_SENSOR
#define SOIL_SENSOR

class SoilSensor {
public:
  virtual int readPercent() = 0;
};

#endif
