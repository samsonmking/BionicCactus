#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H

#include <ESP8266WiFi.h>
#include "persistance/WifiFileHandler.hpp"
#include "time/Clock.hpp"

using namespace Persistance;
using namespace Time;

namespace Wireless {

    class WifiController {
        public:
            WifiController(WifiFileHandler &persistance, Clock &clock);
            void loop();
        private:
            enum States {
                DISCONNECTED,
                AP_CONNECTING,
                AP_CONNECTED,
                CLIENT_CONNECTING,
                CLIENT_CONNECTED,
                DELAY
            };
            States _state;
            WifiFileHandler &_persistance;
            Clock &_clock;
            unsigned long _delayStart;
    };

}

#endif