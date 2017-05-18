#ifndef SOIL_H
#define SOIL_H

#include <PubSubClient.h>
#include <Arduino.h>

class Soil {
public:
  Soil(int chipId, int interval, int signalPin, int powerPin, PubSubClient& mqtt);
  void loop();
private:
  char _topic[30];
  int _signalPin;
  int _powerPin;
  int _interval;
  long _lastMessage = 0;
  PubSubClient& _mqtt;
};

#endif
