#include <SHTSoilProvider.hpp>

SHTSoilProvider::SHTSoilProvider(SHT1x& sht, Pump& pump) : _sht(sht), _pump(pump) {

}

float SHTSoilProvider::getHumidity() {
  return _sht.readHumidity();
}

 unsigned long SHTSoilProvider::getMillis() {
  return millis();
}

void SHTSoilProvider::setPump(int output) {
  _pump.runPump(output);
}

void SHTSoilProvider::stopPump() {
  _pump.stop();
}
