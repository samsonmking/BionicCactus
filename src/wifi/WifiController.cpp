#include "wifi/WifiController.hpp"

using namespace Wireless;

WifiController::WifiController(WifiFileHandler &persistance) :
_persistance(persistance), _state(DISCONNECTED) {

}

void WifiController::loop() {
    switch(_state){
        case DISCONNECTED:
            if (_persistance.isConfigured()) {
                _state = CLIENT_CONNECTING;
            } else {
                _state = AP_CONNECTING;
            }
            break;
        case AP_CONNECTING:
            if (WiFi.softAP("DevAP", "password")) {
                _state = AP_CONNECTED;
            }
            break;
        case AP_CONNECTED:
            if (_persistance.isConfigured()) {
                _state = CLIENT_CONNECTING;
            }
            break;
        case CLIENT_CONNECTING:
            WiFi.begin(_persistance.getSSID(), _persistance.getPassword());
            if (WiFi.waitForConnectResult() == WL_CONNECTED){
                _state = CLIENT_CONNECTED;
            }
            break;
        case CLIENT_CONNECTED:
            if (WiFi.status() != WL_CONNECTED) {
                _state = CLIENT_CONNECTING;
            }
            break;
    }
}