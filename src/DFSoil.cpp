#include <DFSoil.hpp>

DFSoil::DFSoil(int pin, Light& light, int high, int low, int darknessOffset) :
_pin(pin), _light(light), _high(high), _low(low), _darknessOffset(darknessOffset) {
  calculateConstants();
}

int DFSoil::readRaw() {
  return analogRead(_pin);
}

int DFSoil::readPercent() {
  int raw = readRaw();
  if (_light.getLastOutput() == 0) {
    raw += _darknessOffset;
  }
  return calculatePercent(raw);
}

int DFSoil::calculatePercent(int raw) {
  return (raw * _m) + _b;
}

void DFSoil::calculateConstants() {
  _m = 100.0 / (_high - _low);
  _b = 100.0 - (_m * _high);
}
