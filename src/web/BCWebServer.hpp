#ifndef BCWEBSERVER_H
#define BCWEBSERVER_H

#include <ESP8266WebServer.h>
#include <web/GetRequestHandler.hpp>
#include <web/ConfigPageGetRequestHandler.hpp>
#include <web/SettingsFormTemplate.hpp>
#include <web/LightFormTemplate.hpp>
#include <web/PostRequestHandler.hpp>
#include <web/LightPostRequestHandler.hpp>

#include <Light.hpp>

class BCWebServer {
public:
    BCWebServer(ESP8266WebServer *ws, 
        PostRequestHandler *lightPostRequest,
        GetRequestHandler *lightGetRequest);
    void setupServer();
    void loop();
private:
    char _buffer[5000];
    PostParameter _postParams[10];
    ESP8266WebServer *_ws;
    PostRequestHandler *_postLightConfig;
    GetRequestHandler *_getLightConfig;
    void handleGet(GetRequestHandler *request);
    void handlePost(PostRequestHandler *request);
    void redirect(const char *uri);
};

#endif