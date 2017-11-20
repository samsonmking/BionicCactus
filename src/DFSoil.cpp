#include <DFSoil.hpp>

DFSoil::DFSoil(int pin, int high, int low) :
_pin(pin), _high(high), _low(low), _samples(10) {
  calculateConstants();
}

void DFSoil::loop() {
  _samples.add(readPercent());
}

int DFSoil::getPercent() {
  return _samples.getMedian();
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
