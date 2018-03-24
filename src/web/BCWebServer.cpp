#include <web/BCWebServer.hpp>

BCWebServer::BCWebServer(Light *light) : 
_ws(new ESP8266WebServer(80)),
_light(light),
_lightSettingsForm(new LightFormTemplate("/config/light/submit", _light)),
_getLightConfig(new ConfigPageGetRequestHandler("/config/light", "Bionic Cactus Light", "Light Configuration", _lightSettingsForm)) {
    _buffer[0] = 0;
    
}

void BCWebServer::setupServer() {
    // Configure Endpoints
    _ws->on(_getLightConfig->getURI(), [this]() {
        _buffer[0] = 0;
        _getLightConfig->getHTML(_buffer);
        _ws->send(200, "text/html", _buffer);
    });

    _ws->begin();
}

void BCWebServer::loop() {
    _ws->handleClient();
}