#ifndef BCWEBSERVER_H
#define BCWEBSERVER_H

#include <ESP8266WebServer.h>
#include <web/GetRequestHandler.hpp>
#include <web/ConfigPageGetRequestHandler.hpp>
#include <web/SettingsFormTemplate.hpp>
#include <web/LightFormTemplate.hpp>

#include <Light.hpp>

class BCWebServer {
public:
    BCWebServer(Light *light);
    void setupServer();
    void loop();
private:
    char _buffer[5000];
    ESP8266WebServer *_ws;
    Light *_light;
    SettingsFormTemplate *_lightSettingsForm;
    GetRequestHandler *_getLightConfig;
    
};

#endif