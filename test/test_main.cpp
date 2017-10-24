#include <Arduino.h>
#include <unity.h>

#ifdef UNIT_TEST

void setUp(void) {
// set stuff up here
}

void tearDown(void) {
// clean stuff up here
}


void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();    // IMPORTANT LINE!

}

void loop() {
    UNITY_END(); // stop unit testing
}

#endif
