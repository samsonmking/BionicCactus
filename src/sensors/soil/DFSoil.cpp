#include "DFSoil.hpp"

using namespace Sensors::Soil;

DFSoil::DFSoil(int pin) :
  _pin(pin),
  _high(355),
  _low(709),
  _m(0),
  _b(0) {
  calculateConstants();
}

int DFSoil::getPercent() {
  return readPercent();
}

int DFSoil::readRaw() {
  return analogRead(_pin);
}

int DFSoil::readPercent() {
  int raw = readRaw();
  return calculatePercent(raw);
}

int DFSoil::calculatePercent(int raw) {
  return (raw * _m) + _b;
}

void DFSoil::calculateConstants() {
  _m = 100.0 / (_high - _low);
  _b = 100.0 - (_m * _high);
}
