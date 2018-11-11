#include "wifi/WifiController.hpp"

using namespace Time;
using namespace Wireless;

WifiController::WifiController(WifiFileHandler &persistance, MillisProvider& millisProvider) :
_persistance(persistance), _timer(millisProvider, 5, Units::SECONDS), _state(DISCONNECTED) {
    WiFi.setAutoReconnect(true);
}

bool WifiController::isConnected() {
    return _state == CLIENT_CONNECTED;
}

bool WifiController::isAccessPoint() {
    return _state == AP_CONNECTED;
}

void WifiController::loop() {
    switch(_state){
        case DISCONNECTED:
            Serial.println("disconnected");
            if (_persistance.isConfigured()) {
                _state = CLIENT_CONNECTING;
            } else {
                _state = AP_CONNECTING;
            }
            break;
        case AP_CONNECTING:
            WiFi.mode(WIFI_AP);
            if (WiFi.softAP("DevAP", "password")) {
                _state = AP_CONNECTED;
            }
            break;
        case AP_CONNECTED:
            if (_persistance.isConfigured()) {
                _state = DELAY;
                _timer.reset();
            }
            break;
        case CLIENT_CONNECTING:
            WiFi.mode(WIFI_STA);
            WiFi.hostname("bioniccactus");
            WiFi.begin(_persistance.getSSID(), _persistance.getPassword());
            if (WiFi.waitForConnectResult() == WL_CONNECTED){
                _state = CLIENT_CONNECTED;
            }
            Serial.println(WiFi.localIP());
            break;
        case CLIENT_CONNECTED:
            break;
        case DELAY:
            if (!_timer.isExpired()) {
                return;
            }
            if (_persistance.isConfigured()) {
                _state = CLIENT_CONNECTING;
            } else {
                _state = AP_CONNECTING;
            }
            break;
    }
}
