#include <web/BCWebServer.hpp>

BCWebServer::BCWebServer(ESP8266WebServer *ws,
GetRequestHandler *indexGetRequest, 
PostRequestHandler *lightPostRequest,
GetRequestHandler *lightGetRequest,
PostRequestHandler *pumpPostRequest,
GetRequestHandler *pumpGetRequest) : 
_ws(ws),
_getIndex(indexGetRequest),
_postLightConfig(lightPostRequest),
_getLightConfig(lightGetRequest),
_pumpPostRequest(pumpPostRequest),
_pumpGetRequest(pumpGetRequest) {
    resetBuffer();
}

void BCWebServer::setupServer() {
    // Configure Endpoints
    _ws->on(_getIndex->getURI(), [this]() {
        resetBuffer();
        handleGet(_getIndex);
    });
    _ws->on(_getLightConfig->getURI(), [this]() {
        resetBuffer();
        handleGet(_getLightConfig);   
    });
    _ws->on(_postLightConfig->getURI(), [this]() {
        resetBuffer();
        handlePost(_postLightConfig);
        redirect(_getLightConfig->getURI());
    });
    _ws->on(_pumpGetRequest->getURI(), [this]() {
        resetBuffer();
        handleGet(_pumpGetRequest);
    });
    _ws->on(_pumpPostRequest->getURI(), [this]() {
        resetBuffer();
        handlePost(_pumpPostRequest);
        redirect(_pumpGetRequest->getURI());
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

void BCWebServer::resetBuffer() {
    _buffer[0] = 0;
}

void BCWebServer::loop() {
    _ws->handleClient();
}