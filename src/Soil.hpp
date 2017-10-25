#ifndef SOIL_H
#define SOIL_H

#include <PubSubClient.h>
#include <Arduino.h>
#include <SoilProvider.hpp>
#include <QuickStats.h>

class Soil {
public:
  Soil(SoilProvider* provider);
  void setPollingInterval(unsigned long ms) {
    _cycleTime = ms;
  };
  void setSetPoint(float setPoint) {
    _setPoint = setPoint;
  };
  void setVolume(float volume) {
    _volume = volume;
  };
  void setStableCutOff(float cutoff) {
    _stableCutOff = cutoff;
  };
  void loop();
  bool isStable(float *readings);
private:
  SoilProvider* _provider;
  QuickStats _stats;
  float _humidityBuffer[BUFFERSIZE];
  int _bi = 0;
  unsigned long _cycleTime = 600000; // 10 minutes
  float _setPoint = 90;
  float _stableCutOff = 0.5;
  float _volume = 400;
  bool _pumping = false;
};

#endif
