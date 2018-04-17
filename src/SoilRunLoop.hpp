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
  int getSetPoint() {
    return _setPoint;
  }
  void setTolerance(int tolerance) {
    _tolerance = tolerance;
  }
  int getTolerance() {
    return _tolerance;
  }
  void setMaxDispense(int max) {
    _maxDispense = max;
  }
  int getMaxDispense() {
    return _maxDispense;
  }
  void setmlPerPercent(int scale) {
    _mlPerPercent = scale;
  }
  int getmlPerPercent() {
    return _mlPerPercent;
  }
  void setHrsAtMoisture(int hrs) {
    _timeAtMoisture = MILLISPERHOUR * (unsigned long)hrs;
  };
  int getHrsAtMoisture() {
    return _timeAtMoisture / MILLISPERHOUR;
  }
  void setHrsDry(int hrs) {
    _timeAtDry = MILLISPERHOUR * (unsigned long)hrs;
  };
  int getHrsDry() {
    return _timeAtDry / MILLISPERHOUR;
  }
  void setDispersionMin(int min) {
    _disperseTime = MILLISPERMIN * (unsigned long)min;
  }
  int getDispersionMin() {
    return _disperseTime / MILLISPERMIN;
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
  float _mlPerPercent = 4;
  const static unsigned long MILLISPERHOUR = 3600000;
  const static unsigned long MILLISPERMIN = 60000;
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
