#include <PeriPump.hpp>

PeriPump::PeriPump(Clock& clock, int pinOut1, int pinOut2, int pinPWM) :
_clock(clock), _pinOut1(pinOut1), _pinOut2(pinOut2), _pinPWM(pinPWM), _stopTime(0), _flowRate(1.2l) {
  pinMode(_pinOut1, OUTPUT);
  pinMode(_pinOut2, OUTPUT);
  stop();
}

double PeriPump::getFlowRate() {
  return _flowRate;
}

void PeriPump::setFlowRate(double flowRate) {
  _flowRate = flowRate;
}

void PeriPump::runPump(int speed, Directions dir) {
  if (dir == Forward)
  {
    digitalWrite(_pinOut1, HIGH);
    digitalWrite(_pinOut2, LOW);
  }
  else {
    digitalWrite(_pinOut1, LOW);
    digitalWrite(_pinOut2, HIGH);
  }
  int pwmVal = (speed * PWMRANGE) / 100;
  analogWrite(_pinPWM, pwmVal);
}

void PeriPump::stop() {
  analogWrite(_pinPWM, 0);
  digitalWrite(_pinOut1, HIGH);
  digitalWrite(_pinOut2, HIGH);
}

void PeriPump::setVolume(int vol) {
  _startTime = _clock.getMillis();
  int secs = (((vol / _flowRate) * _speed) / 100);
  _stopTime = (1000 * (unsigned long)secs) + _startTime;
}

void PeriPump::loop() {
  if (dispenseDone()) {
    stop();
  }
  else {
    runPump(_speed, Forward);
  }
}

bool PeriPump::dispenseDone() {
  unsigned long now = _clock.getMillis();
  if (now < _stopTime)  {
    return false;
  }
  return true;
}
