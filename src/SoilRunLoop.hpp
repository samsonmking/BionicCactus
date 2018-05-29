#ifndef SOIL_RUNLOOP_H
#define SOIL_RUNLOOP_H

#include <Arduino.h>
#include "sensors/pump/Pump.hpp"
#include "sensors/soil/SoilSensor.hpp"
#include "time/MillisProvider.hpp"
#include "time/Timer.hpp"

class SoilRunLoop {
public:
  SoilRunLoop(Sensors::Pump::Pump* pump, Sensors::Soil::SoilSensor& sensor, Time::MillisProvider& millisProvider);
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
    _timeAtMoisture = (unsigned long)hrs;
  };
  int getHrsAtMoisture() {
    return _timeAtMoisture;
  }
  void setHrsDry(int hrs) {
    _timeAtDry = (unsigned long)hrs;
  };
  int getHrsDry() {
    return _timeAtDry;
  }
  void setDispersionMin(int min) {
    _disperseTime = (unsigned long)min;
  }
  int getDispersionMin() {
    return _disperseTime;
  }
  void loop();
private:
  States _state;
  Sensors::Pump::Pump* _pump;
  Sensors::Soil::SoilSensor& _sensor;
  Time::Timer _cycleTimer;
  Time::Timer _dispersionTimer;
  int _setPoint;
  int _tolerance; 
  int _maxDispense;
  float _mlPerPercent;
  unsigned long _disperseTime;
  unsigned long _timeAtMoisture;
  unsigned long _timeAtDry;
  void enterCheckMoisture();
  void checkMoisture();
  void enterPumping(int vol);
  void pumping();
  void enterDispersing();
  void dispersing();
  void enterDrying();
  void drying();
};

#endif
