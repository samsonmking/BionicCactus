#include "LIDARBottle.hpp"

using namespace Sensors::Bottle;

LidarBottle::LidarBottle(): 
_lox(Adafruit_VL53L0X()), 
_a0{-47.3}, 
_a1{3.54}, 
_a2{-0.021}, 
_buffer(CircularBuffer<int, 200>()), 
_failCount(0),
_resetPin(D5),
_lowerBound(50),
_upperBound(250) {
    
}

void LidarBottle::setup() {
    _lox.begin();
    pinMode(_resetPin, OUTPUT);
    digitalWrite(_resetPin, HIGH);
}

void LidarBottle::loop() {
    VL53L0X_RangingMeasurementData_t measure;
    _lox.rangingTest(&measure, false);
    uint16_t mm = measure.RangeMilliMeter;
    if (measure.RangeStatus != 0 || mm < _lowerBound || mm > _upperBound) {
        _failCount++;
    } else {
        _buffer.push(mm);
    }

    if(_failCount > 200) {
        resetSensor();
        _failCount = 0;
    }
}

int LidarBottle::getPercent() {
    if (_buffer.size() == 0) return 0;
    int avg = 0;
    for(uint i = 0; i < _buffer.size(); i++) {
        avg += _buffer[i];
    }
    avg = avg / _buffer.size();
    avg = calculatePercent(avg);
    return avg;
}

int LidarBottle::calculatePercent(int mm) {
    int percent = _a0 + (_a1 * mm) + (_a2 * sq(mm));
    if (percent > 100 ) {
        return 100;
    }
    else if(percent < 0) {
        return 0;
    }
    return percent;
}

void LidarBottle::resetSensor() {
    digitalWrite(_resetPin, LOW);
    delay(10);
    digitalWrite(_resetPin, HIGH);
    _lox.begin();
}