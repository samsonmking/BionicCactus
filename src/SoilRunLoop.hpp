#ifndef SOIL_RUNLOOP_H
#define SOIL_RUNLOOP_H

#include <Arduino.h>
#include "sensors/pump/Pump.hpp"
#include "sensors/soil/SoilSensor.hpp"
#include "time/Clock.hpp"

class SoilRunLoop {
public:
  SoilRunLoop(Sensors::Pump::Pump* pump, Sensors::Soil::SoilSensor& sensor, Time::Clock& clock);
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
  Sensors::Pump::Pump* _pump;
  Sensors::Soil::SoilSensor& _sensor;
  Time::Clock& _clock;
  int _setPoint;
  int _tolerance; 
  int _maxDispense;
  float _mlPerPercent;
  const static unsigned long MILLISPERHOUR = 3600000;
  const static unsigned long MILLISPERMIN = 60000;
  unsigned long _disperseTime;
  unsigned long _disperseStarted;
  unsigned long _timeAtMoisture;
  unsigned long _moistureStarted;
  unsigned long _timeAtDry;
  unsigned long _dryStarted;
  void checkMoisture();
  void pumping();
  void dispersing();
  void drying();
};

#endif
