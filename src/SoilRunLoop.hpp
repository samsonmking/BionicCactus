#ifndef SOIL_RUNLOOP_H
#define SOIL_RUNLOOP_H

#include <Arduino.h>
#include <Pump.hpp>
#include <SoilSensor.hpp>
#include <Clock.hpp>

class SoilRunLoop {
public:
  SoilRunLoop(Pump* pump, SoilSensor* sensor, Clock& clock);
  enum States { Dispersing, Pumping, CheckMoisture, Drying };
  States getState() {
    return _state;
  }
  void setSetPoint(int setPoint) {
    _setPoint = setPoint;
  };
  void setTolerance(int tolerance) {
    _tolerance = tolerance;
  }
  void setMaxDispense(int max) {
    _maxDispense = max;
  }
  void setmlPerPercent(int scale) {
    _mlPerPercent = scale;
  }
  void setHrsAtMoisture(int hrs) {
    _timeAtMoisture = 3600000 * (unsigned long)hrs;
  };
  void setHrsDry(int hrs) {
    _timeAtDry = 3600000 * (unsigned long)hrs;
  };
  void setDispersionMin(int min) {
    _disperseTime = 60000 * (unsigned long)min;
  }
  void loop();
private:
  States _state;
  Pump* _pump;
  SoilSensor* _sensor;
  Clock _clock;
  int _setPoint = 85;
  int _tolerance = 1;
  int _maxDispense = 50;
  float _mlPerPercent = 2;
  //unsigned long _disperseTime = 600000;
  unsigned long _disperseTime = 200000;
  unsigned long _disperseStarted;
  unsigned long _timeAtMoisture = 43200000;
  unsigned long _moistureStarted;
  unsigned long _timeAtDry = 43200000;
  unsigned long _dryStarted;
  void checkMoisture();
  void pumping();
  void dispersing();
  void drying();
};

#endif
