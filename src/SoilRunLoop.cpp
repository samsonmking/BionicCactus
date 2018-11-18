#include <SoilRunLoop.hpp>

using namespace Time;
using namespace Sensors::Pump;
using namespace Sensors::Soil;

SoilRunLoop::SoilRunLoop(Pump* pump, SoilSensor& sensor, MillisProvider& millisProvider) : 
_pump(pump), 
_sensor(sensor), 
_cycleTimer(millisProvider, 0, Units::SECONDS), 
_dispersionTimer(millisProvider, 5, Units::MINUTES),
_state(Dispersing),
_setPoint{85},
_tolerance{1},
_maxDispense{50},
_mlPerPercent{4},
_disperseTime{5},
_timeAtMoisture{8},
_timeAtDry{16} {
  enterDispersing();
}

void SoilRunLoop::setEnabled(bool enabled) {
    if(!enabled) {
        _state = Disabled;
    } else if(enabled && _state == Disabled) {
        enterDispersing();       
    }
}

bool SoilRunLoop::getEnabled() {
    return _state != Disabled;
}

void SoilRunLoop::loop() {
  switch (_state) {
    case CheckMoisture:
      checkMoisture();
      break;
    case Pumping:
      pumping();
      break;
    case Dispersing:
      dispersing();
      break;
    case Drying:
      drying();
      break;
    case Disabled:
      break;
  }
}

void SoilRunLoop::enterCheckMoisture() {
  _cycleTimer.reset(_timeAtMoisture, Units::HOURS);
  _state = CheckMoisture;
}

void SoilRunLoop::checkMoisture() {
  if (_cycleTimer.isExpired()) {
    enterDrying();
    return;
  }

  int current = _sensor.getPercent();
  int diff = _setPoint - current;
  if (diff > _tolerance) {
    int vol = _mlPerPercent * diff;
    if (vol > _maxDispense) {
      vol = _maxDispense;
    }
    enterPumping(vol);
  }
}

void SoilRunLoop::enterPumping(int vol) {
    _pump->setVolume(vol);
    _state = Pumping;
}

void SoilRunLoop::pumping() {
  if (_pump->dispenseDone()) {
    enterDispersing();
  }
}

void SoilRunLoop::enterDispersing() {
  _dispersionTimer.reset(_disperseTime, Units::MINUTES);
  _state = Dispersing;
}

void SoilRunLoop::dispersing() {
  if (_dispersionTimer.isExpired()) {
    enterCheckMoisture();
  }
}

void SoilRunLoop::enterDrying() {
  _cycleTimer.reset(_timeAtDry, Units::HOURS);
  _state = Drying;
}

void SoilRunLoop::drying() {
  if (_cycleTimer.isExpired()) {
    enterCheckMoisture();
  }
}
