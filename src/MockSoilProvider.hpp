#ifndef MOCKSOILPROVIDER_H
#define MOCKSOILPROVIDER_H

#include <SoilProvider.hpp>

class MockSoilProvider : public SoilProvider {
public:
  virtual float getHumidity() {
    return _humidity;
  };
  void setHumidity(float humidity) {
    _humidity = humidity;
  };
  virtual unsigned long getMillis() {
    return _currentMillis;
  };
  void setMillis(unsigned long m) {
    _currentMillis = m;
  };
  virtual void setPump(int output) {
    _pumpOutput = output;
  };
  virtual void stopPump() {
    _pumpOutput = 0;
  }
  int getPumpOutput() {
    return _pumpOutput;
  };
private:
  float _humidity = 50;
  unsigned long _currentMillis = 0;
  int _pumpOutput = 0;
};

#endif
