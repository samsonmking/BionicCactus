#include "ScaleBottle.hpp"

using namespace Sensors::Bottle;

ScaleBottle::ScaleBottle(int dout, int sck) :
_scale(HX711()),
_empty{522450},
_full{1182400},
_m{0},
_b{0},
_dout{dout},
_sck{sck} {
    calculateConstants();
}

void ScaleBottle::init() {
    _scale.begin(_dout, _sck);
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

long ScaleBottle::getEmpty() {
    return _empty;
}

void ScaleBottle::setEmpty(long empty) {
    _empty = empty;
    calculateConstants();
}

long ScaleBottle::getFull() {
    return _full;
}

void ScaleBottle::setFull(long full) {
    _full = full;
    calculateConstants();
}

void ScaleBottle::calculateConstants() {
  _m = 100.0 / (_full - _empty);
  _b = 100.0 - (_m * _full);
}
