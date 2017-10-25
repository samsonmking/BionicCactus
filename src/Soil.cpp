#include <Soil.hpp>

Soil::Soil(SHT1x& sht1x, Pump& pump) : _sht1x(sht1x), _pump(pump), _stats(), pumping(false) {

}

void Soil::loop() {
  if (pumping) {
    _pump.runPump(100);
    unsigned long now = millis();
    if ((now - _startTime) > _cycleTime) {
      pumping = false;
      return;
    }
  }
  else {
    _pump.runPump(0);
    float humidity = _sht1x.readHumidity();
    _humidityBuffer[_bi] = humidity;
    if (_bi < (_bufferSize - 1)) {
      _bi++;
    }
    else {
      _bi = 0;
    }
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println();
    float stdDev = _stats.stdev(_humidityBuffer, _bufferSize);
    Serial.println(stdDev);
    if ((stdDev < 0.05) && (humidity < 85.0)) {
      pumping = true;
      _startTime = millis();
     }
   }
}
