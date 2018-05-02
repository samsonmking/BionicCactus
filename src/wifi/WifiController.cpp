#include "wifi/WifiController.hpp"

using namespace Wireless;

WifiController::WifiController(WifiFileHandler &persistance, Clock &clock) :
_persistance(persistance), _clock(clock), _state(DISCONNECTED) {
    WiFi.setAutoReconnect(false);
}

bool WifiController::isConnected() {
    return _state == CLIENT_CONNECTED;
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
                _delayStart = _clock.getMillis();
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
            if (!WiFi.isConnected()) {
                _state = CLIENT_CONNECTING;
                Serial.println("wifi lost");
            }
            break;
        case DELAY:
            if (_clock.getMillis() - _delayStart < 5000) {
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