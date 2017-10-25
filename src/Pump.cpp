#include <Pump.hpp>

Pump::Pump(int pinOut1, int pinOut2, int pinPWM) {
  _pinOut1 = pinOut1;
  _pinOut2 = pinOut2;
  _pinPWM = pinPWM;
  pinMode(_pinOut1, OUTPUT);
  pinMode(_pinOut2, OUTPUT);
  stop();
}

void Pump::runPump(int speed) {
  digitalWrite(_pinOut1, HIGH);
  digitalWrite(_pinOut2, LOW);
  int pwmVal = (speed * PWMRANGE) / 100;
  analogWrite(_pinPWM, pwmVal);
}

void Pump::stop() {
  digitalWrite(_pinOut1, HIGH);
  digitalWrite(_pinOut2, HIGH);
}
