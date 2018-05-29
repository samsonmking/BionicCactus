#ifndef ARDUINO_MILLIS_PROVIDER_H
#define ARDUINO_MILLIS_PROVIDER_H

#include "MillisProvider.hpp"
#include <Arduino.h>

namespace Time {

    class ArduinoMillisProvider : public MillisProvider {
        public:
            unsigned long getMillis() override;
    };

}

#endif