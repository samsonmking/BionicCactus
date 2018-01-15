#ifndef LIDARBOTTLE_H
#define LIDARBOTTLE_H

#include <Adafruit_VL53L0X.h>
#include <CircularBuffer.h>

class LidarBottle {
public:
    LidarBottle();
    int getPercent();
    void loop();
    void setA0(float a0) {
        _a0 = a0;
    };
    float getA0() {
        return _a0;
    };
    void setA1(float a1) {
        _a1 = a1;
    }
    float getA1() {
        return _a1;
    };
    void setA2(float a2) {
        _a2 = a2;
    }
    float getA2() {
        return _a2;
    }
    int calculatePercent(int mm);
private:
    Adafruit_VL53L0X _lox;
    CircularBuffer<int, 200> _buffer;
    float _a0;
    float _a1;
    float _a2;
};

#endif