#ifndef LIGHT_H
#define LIGHT_H

class Light {
public:
  virtual void loop() = 0;
  virtual bool isOn() = 0;
};

#endif
