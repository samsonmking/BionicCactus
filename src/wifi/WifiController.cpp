#include "wifi/WifiController.hpp"

using namespace Time;
using namespace Wireless;

WifiController::WifiController(int triggerPin, 
        WifiFileHandler &persistance, 
        MillisProvider& millisProvider) :
        _triggerPin(triggerPin),
        _persistance(persistance), 
        _timer(millisProvider, 5, Units::SECONDS), 
        _state(DISCONNECTED) {
    pinMode(_triggerPin, INPUT);
    WiFi.setAutoReconnect(true);
}

bool WifiController::isConnected() {
    return _state == CLIENT_CONNECTED;
}

bool WifiController::isAccessPoint() {
    return _state == AP_CONNECTED;
}

void WifiController::clientMode() {
    if (_persistance.isConfigured()) {
        _state = DELAY;
        _timer.reset();
    }
}

void WifiController::loop() {
    switch(_state){
        case DISCONNECTED:
            disconnected();
            break;
        case AP_CONNECTING:
             apConnecting();
            break;
        case AP_CONNECTED:
            break;
        case CLIENT_CONNECTING:
            clientConnecting();
            break;
        case CLIENT_CONNECTED:
            clientConnected();
            break;
        case DELAY:
            delay();
            break;
    }
}

void WifiController::disconnected() {
    if (switchToAP()) {
        return;
    }
    if (_persistance.isConfigured()) {
        _state = CLIENT_CONNECTING;
    } else {
        _state = AP_CONNECTING;
    }
}

void WifiController::apConnecting() {
    WiFi.mode(WIFI_AP);
    if (WiFi.softAP("bc_wifi_setup", "password")) {
        _state = AP_CONNECTED;
    }
}

void WifiController::clientConnecting() {
    if (switchToAP()) {
        return;
    }
    WiFi.mode(WIFI_STA);
    WiFi.hostname(_persistance.getHostname());
    WiFi.begin(_persistance.getSSID(), _persistance.getPassword());
    if (WiFi.waitForConnectResult() == WL_CONNECTED){
        _state = CLIENT_CONNECTED;
    }
    Serial.println(WiFi.localIP());
}

void WifiController::clientConnected() {
    switchToAP();
}

void WifiController::delay() {
    if (!_timer.isExpired()) {
        return;
    }
    if (_persistance.isConfigured()) {
        _state = CLIENT_CONNECTING;
    } else {
        _state = AP_CONNECTING;
    }
}

bool WifiController::switchToAP() {
    if (digitalRead(_triggerPin) == LOW) {
        _state = AP_CONNECTING;
        Serial.println("trigger");
        return true;
    }
    return false;
}
