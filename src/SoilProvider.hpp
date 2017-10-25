#ifndef SOILPROVIDER_H
#define SOILPROVIDER_H
#define BUFFERSIZE 10
class SoilProvider {
public:
  virtual float getHumidity() = 0;
  virtual unsigned long getMillis() = 0;
  virtual void setPump(int output) = 0;
  virtual void stopPump() = 0;
};

#endif
