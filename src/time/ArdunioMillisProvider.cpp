#include "ArduinoMillisProvider.hpp"

namespace Time {

    inline unsigned long ArduinoMillisProvider::getMillis() {
        return millis();
    }

}

