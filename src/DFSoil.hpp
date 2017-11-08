#ifndef DFSOIL_H
#define DFSOIL_H

#include <Arduino.h>
#include <Light.hpp>

class DFSoil {
public:
  DFSoil(int pin, Light& light, int high = 419, int low = 770, int darknessOffset = 59);
  void setHigh(int high) {
    _high = high;
    calculateConstants();
  };
  void setLow(int low) {
    _low = low;
    calculateConstants();
  };
  void setDarknessOffset(int offset) {
    _darknessOffset = offset;
  };
  int readRaw();
  int readPercent();
  int calculatePercent(int raw);
private:
  void calculateConstants();
  Light _light;
  int _pin;
  int _high;
  int _low;
  int _darknessOffset;
  float _m;
  float _b;
};

#endif
