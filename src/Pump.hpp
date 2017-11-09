#ifndef PUMP_H
#define PUMP_H

class Pump {
public:
  virtual void setVolume(int vol) = 0;
  virtual bool dispenseDone() = 0;
  virtual void loop() = 0;
  virtual void prime() = 0;
  virtual void empty() = 0;
};

#endif
