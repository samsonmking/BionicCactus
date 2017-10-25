#ifndef PUMP_H
#define PUMP_H

#include<Arduino.h>

class Pump {
public:
  Pump(int pinOut1, int pinOut2, int pinPWM);
  void runPump(int speed);
  void empty(int speed);
  void stop();
private:
  int _pinOut1;
  int _pinOut2;
  int _pinPWM;
};

#endif
