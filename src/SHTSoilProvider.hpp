#ifndef SHTSOILPROVIDER
#define SHTSOILPROVIDER

#include <SoilProvider.hpp>
#include <SHT1x.h>
#include <Pump.hpp>

class SHTSoilProvider : public SoilProvider {
public:
  SHTSoilProvider(SHT1x& sht, Pump& pump);
  virtual float getHumidity();
  virtual unsigned long getMillis();
  virtual void setPump(int output);
  virtual void stopPump();
private:
  SHT1x _sht;
  Pump _pump;
};

#endif
