#ifndef BCWEBSERVER_H
#define BCWEBSERVER_H

#include <ESP8266WebServer.h>
#include <web/GetRequestHandler.hpp>
#include <web/PostRequestHandler.hpp>
#include <wifi/WifiController.hpp>

using namespace Persistance;
using namespace Wireless;

class BCWebServer {
public:
    BCWebServer(ESP8266WebServer *ws, 
        GetRequestHandler &indexGetRequest,
        PostRequestHandler &wifiPostRequest,
        GetRequestHandler &wifiGetRequest,
        WifiController &wifiController);
    void contributeGetRequest(GetRequestHandler &getRequest);
    void contributePostRequest(PostRequestHandler &postRequest, const char* redirectUri);
    void setupServer();
    void loop();
private:
    char _buffer[5000];
    PostParameter _postParams[10];
    ESP8266WebServer *_ws;
    GetRequestHandler &_getIndex;
    PostRequestHandler &_wifiPostRequest;
    GetRequestHandler &_wifiGetRequest;
    WifiController &_wifiController;
    void handleGet(GetRequestHandler &request);
    void handlePost(PostRequestHandler &request);
    void redirect(const char *uri);
    void resetBuffer();
};

#endif
