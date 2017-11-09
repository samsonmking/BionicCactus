#ifndef MOCK_SENSOR_H
#define MOCK_SENSOR_H

#include<SoilSensor.hpp>

class MockSoilSensor : public SoilSensor {
public:
  int percent = 0;
  virtual int readPercent() {
    return percent;
  };
};

#endif
