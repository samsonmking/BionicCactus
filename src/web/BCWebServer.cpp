#include <web/BCWebServer.hpp>

BCWebServer::BCWebServer(ESP8266WebServer *ws,
GetRequestHandler *indexGetRequest, 
PostRequestHandler *lightPostRequest,
GetRequestHandler *lightGetRequest) : 
_ws(ws),
_getIndex(indexGetRequest),
_postLightConfig(lightPostRequest),
_getLightConfig(lightGetRequest) {
    _buffer[0] = 0;
}

void BCWebServer::setupServer() {
    // Configure Endpoints
    _ws->on(_getIndex->getURI(), [this]() {
        _buffer[0] = 0;
        handleGet(_getIndex);
    });
    _ws->on(_getLightConfig->getURI(), [this]() {
        _buffer[0] = 0;
        handleGet(_getLightConfig);   
    });
    _ws->on(_postLightConfig->getURI(), [this]() {
        _buffer[0] = 0;
        handlePost(_postLightConfig);
        redirect(_getLightConfig->getURI());
    });
    _ws->begin();
}

void BCWebServer::handleGet(GetRequestHandler *request) {
    request->getHTML(_buffer, sizeof(_buffer));
    _ws->send(200, "text/html", _buffer);
}

void BCWebServer::handlePost(PostRequestHandler *request) {
    int args = _ws->args();
    for(int i = 0; i < args; i++) {
        strcpy(_postParams[i].key, _ws->argName(i).c_str());
        strcpy(_postParams[i].value, _ws->arg(i).c_str());
    }
    request->setVals(_postParams, args);
}

void BCWebServer::redirect(const char *uri) {
    _ws->sendHeader("Location", uri, true);
    _ws->send(302, "text/plain", "");
}

void BCWebServer::loop() {
    _ws->handleClient();
}