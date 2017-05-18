#include <Soil.h>

Soil::Soil(int chipId, int interval, int signalPin, int powerPin, PubSubClient& mqtt): _mqtt(mqtt) {
  snprintf(_topic, 30, "/soil/%i/values", chipId);
  _interval = interval;
  _signalPin = signalPin;
  _powerPin = powerPin;
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);
}

void Soil::loop() {
  long now = millis();
  if ((now - _lastMessage) < _interval) {
    return;
  }
  digitalWrite(_powerPin, HIGH);
  delay(500);
  int sensorValue = analogRead(_signalPin);
  int sensorPercent = (sensorValue  * 100) / 1023;
  char sensorStr[5];
  itoa(sensorPercent, sensorStr, 10);
  _mqtt.publish(_topic, sensorStr);
  _lastMessage = now;
  digitalWrite(_powerPin, LOW);
}
