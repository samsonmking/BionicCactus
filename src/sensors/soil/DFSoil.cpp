#include "DFSoil.hpp"

using namespace Sensors::Soil;
using namespace Time;

DFSoil::DFSoil(int pin, Clock &clock) :
  _pin(pin),
  _clock(clock),
  _high(355),
  _low(709),
  _m(0),
  _b(0),
  _lastAverage(0),
  _lastRead{0} {
  calculateConstants();
}

void DFSoil::loop() {
  unsigned long now = _clock.getMillis();
  if (now - _lastRead < 100) {
    return;
  }
  _buffer.push(readPercent());
  int sum = 0;
  for (int i = 0; i < _buffer.size(); i++) {
    sum += _buffer[i];
  }
  _lastAverage = sum / _buffer.size();
  _lastRead = now;
}

int DFSoil::getPercent() {
  return _lastAverage;
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
