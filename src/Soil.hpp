#ifndef SOIL_H
#define SOIL_H

#include <PubSubClient.h>
#include <Arduino.h>
#include <SHT1x.h>
#include <Pump.hpp>
#include <QuickStats.h>

class Soil {
public:
  Soil(SHT1x& sht1x, Pump& pump);
  void setTimeAtWet(long seconds);
  void setTimeAtDry(long seconds);
  void setDispersionTime(long seconds);
  void loop();
private:
  SHT1x _sht1x;
  Pump _pump;
  QuickStats _stats;
  static const int _bufferSize = 10;
  float _humidityBuffer[_bufferSize];
  int _bi = 0;
  unsigned long _cycleTime = 500;
  unsigned long _startTime = 0;
  float _setPoint = 95;
  bool pumping;
};

#endif
