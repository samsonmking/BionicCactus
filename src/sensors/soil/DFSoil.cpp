#include "DFSoil.hpp"

using namespace Sensors::Soil;
using namespace Time;

DFSoil::DFSoil(int pin, MillisProvider& millisProvider) :
  _pin(pin),
  _timer(millisProvider, 100, Units::MILLISECONDS),
  _high(355),
  _low(709),
  _m(0),
  _b(0),
  _lastAverage(0) {
  calculateConstants();
}

void DFSoil::loop() {
  if (!_timer.isExpired()) {
    return;
  }
  _buffer.push(readPercent());
  int sum = 0;
  for (int i = 0; i < _buffer.size(); i++) {
    sum += _buffer[i];
  }
  _lastAverage = sum / _buffer.size();
  _timer.reset();
}

int DFSoil::getPercent() {
  return _lastAverage;
}

int DFSoil::getRaw() {
  return analogRead(_pin);
}

int DFSoil::readPercent() {
  int raw = getRaw();
  return calculatePercent(raw);
}

int DFSoil::calculatePercent(int raw) {
  return (raw * _m) + _b;
}

void DFSoil::calculateConstants() {
  _m = 100.0 / (_high - _low);
  _b = 100.0 - (_m * _high);
}
