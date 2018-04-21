#ifndef BCWEBSERVER_H
#define BCWEBSERVER_H

#include <ESP8266WebServer.h>
#include <web/GetRequestHandler.hpp>
#include <web/ConfigPageGetRequestHandler.hpp>
#include <web/SettingsFormTemplate.hpp>
#include <web/PostRequestHandler.hpp>

#include <Light.hpp>

class BCWebServer {
public:
    BCWebServer(ESP8266WebServer *ws, 
        GetRequestHandler *indexGetRequest,
        PostRequestHandler *lightPostRequest,
        GetRequestHandler *lightGetRequest,
        PostRequestHandler *pumpPostRequest,
        GetRequestHandler *pumpGetRequest,
        PostRequestHandler *soilPostRequest,
        GetRequestHandler *soilGetRequest,
        PostRequestHandler *runLoopPostRequest,
        GetRequestHandler *runLoopGetRequest);
    void setupServer();
    void loop();
private:
    char _buffer[5000];
    PostParameter _postParams[10];
    ESP8266WebServer *_ws;
    PostRequestHandler *_postLightConfig;
    GetRequestHandler *_getLightConfig;
    GetRequestHandler *_getIndex;
    PostRequestHandler *_pumpPostRequest;
    GetRequestHandler *_pumpGetRequest;
    PostRequestHandler *_soilPostRequest;
    GetRequestHandler *_soilGetRequest;
    PostRequestHandler *_runLoopPostRequest;
    GetRequestHandler *_runLoopGetRequest;
    void handleGet(GetRequestHandler *request);
    void handlePost(PostRequestHandler *request);
    void redirect(const char *uri);
    void resetBuffer();
};

#endif