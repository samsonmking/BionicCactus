#include "ScaleBottle.hpp"

using namespace Sensors::Bottle;

ScaleBottle::ScaleBottle(int dout, int sck) :
_scale(HX711(dout, sck)),
_low{522450},
_high{1182400},
_m{0},
_b{0} {
    calculateConstants();
}

long ScaleBottle::getRaw() {
    return _scale.read_average(3);
}

int ScaleBottle::getPercent() {
    int result = (getRaw() * _m) + _b;
    if (result < 0) {
        return 0;
    }
    if (result > 100) {
        return 100;
    }
    return result;
}

void ScaleBottle::calculateConstants() {
  _m = 100.0 / (_high - _low);
  _b = 100.0 - (_m * _high);
}