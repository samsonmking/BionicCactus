#include <Soil.hpp>

Soil::Soil(SoilProvider* provider): _provider(provider), _stats() {

}

void Soil::loop() {

}

bool Soil::isStable(float *readings) {
  float stdDev = _stats.stdev(readings, _bufferSize);
  return stdDev <= _stableCutOff;
}
