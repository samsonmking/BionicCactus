#ifndef PERI_PUMP_H
#define PERI_PUMP_H

#include <Pump.hpp>
#include <Arduino.h>
#include <Clock.hpp>

class PeriPump : public Pump {
public:
  PeriPump(Clock& clock, int pinOut1, int pinOut2, int pinPWM);
  enum Directions { Forward, Backward };
  virtual void setVolume(int vol);
  virtual bool dispenseDone();
  virtual void loop();
  virtual void prime() {
    runPump(100, Forward);
  };
  virtual void empty() {
    runPump(100, Backward);
  }
  void setSpeed(int speed) {
    _speed = speed;
  };
  void setFlowRate(int flowRate) {
    _flowRate = flowRate;
  };
  void runPump(int speed, Directions dir);
  void stop();
private:
  Clock _clock;
  int _pinOut1;
  int _pinOut2;
  int _pinPWM;
  int _speed = 100;
  float _flowRate = 0.9;
  unsigned long _startTime;
  unsigned long _stopTime;
};

#endif
