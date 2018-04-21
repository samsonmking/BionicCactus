#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H

#include <ESP8266WiFi.h>
#include "persistance/WifiFileHandler.hpp"

using namespace Persistance;

namespace Wireless {

    class WifiController {
        public:
            WifiController(WifiFileHandler &persistance);
            // bool isConnected();
            // bool isConfigured();
            // void StartAPMode();
            // void StartClientMode();
            void loop();
        private:
            enum States {
                DISCONNECTED,
                AP_CONNECTING,
                AP_CONNECTED,
                CLIENT_CONNECTING,
                CLIENT_CONNECTED
            };
            States _state;
            WifiFileHandler &_persistance;
    };

}

#endif