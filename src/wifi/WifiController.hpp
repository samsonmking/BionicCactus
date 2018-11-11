#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H

#include <ESP8266WiFi.h>
#include "persistance/WifiFileHandler.hpp"
#include "time/MillisProvider.hpp"
#include "time/Timer.hpp"

using namespace Persistance;

namespace Wireless {

    class WifiController {
        public:
            WifiController(int triggerPin,
                    WifiFileHandler &persistance, 
                    Time::MillisProvider& millisProvider);
            void loop();
            bool isConnected();
            bool isAccessPoint();
            void clientMode();
        private:
            void disconnected();
            void apConnecting();
            void clientConnecting();
            void clientConnected();
            void delay();
            bool switchToAP();
            enum States {
                DISCONNECTED,
                AP_CONNECTING,
                AP_CONNECTED,
                CLIENT_CONNECTING,
                CLIENT_CONNECTED,
                DELAY
            };
            States _state;
            int _triggerPin;
            WifiFileHandler &_persistance;
            Time::Timer _timer;
    };

}

#endif
