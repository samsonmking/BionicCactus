#include <web/BCWebServer.hpp>

BCWebServer::BCWebServer(ESP8266WebServer *ws,
GetRequestHandler *indexGetRequest, 
PostRequestHandler *lightPostRequest,
GetRequestHandler *lightGetRequest,
PostRequestHandler *pumpPostRequest,
GetRequestHandler *pumpGetRequest,
PostRequestHandler *soilPostRequest,
GetRequestHandler *soilGetRequest,
PostRequestHandler *runLoopPostRequest,
GetRequestHandler *runLoopGetRequest,
PostRequestHandler *wifiPostRequest,
GetRequestHandler *wifiGetRequest,
WifiFileHandler &wifiSettings,
PostRequestHandler *emailPostRequest,
GetRequestHandler *emailGetRequest) : 
_ws(ws),
_getIndex(indexGetRequest),
_postLightConfig(lightPostRequest),
_getLightConfig(lightGetRequest),
_pumpPostRequest(pumpPostRequest),
_pumpGetRequest(pumpGetRequest),
_soilPostRequest(soilPostRequest),
_soilGetRequest(soilGetRequest),
_runLoopPostRequest(runLoopPostRequest),
_runLoopGetRequest(runLoopGetRequest),
_wifiPostRequest(wifiPostRequest),
_wifiGetRequest(wifiGetRequest),
_wifiSettings(wifiSettings),
_emailPostRequest(emailPostRequest),
_emailGetRequest(emailGetRequest) {
    resetBuffer();
}

void BCWebServer::setupServer() {
    // Configure Endpoints
    _ws->on(_getIndex->getURI(), [this]() {
        resetBuffer();
        if (_wifiSettings.isConfigured()) {
            handleGet(_getIndex);
        } else {
            redirect(_wifiGetRequest->getURI());
        }
    });
    _ws->on(_wifiGetRequest->getURI(), [this]() {
        resetBuffer();
        handleGet(_wifiGetRequest);
    });
    _ws->on(_wifiPostRequest->getURI(), [this]() {
        resetBuffer();
        handlePost(_wifiPostRequest);
        _ws->send(200, "text/plain", "WiFi will disconnect in 5 seconds. Refresh and check connection.");
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
    _ws->on(_soilPostRequest->getURI(), [this]() {
        resetBuffer();
        handlePost(_soilPostRequest);
        redirect(_soilGetRequest->getURI());
    });
    _ws->on(_soilGetRequest->getURI(), [this]() {
        resetBuffer();
        handleGet(_soilGetRequest);
    });
    _ws->on(_runLoopPostRequest->getURI(), [this]() {
        resetBuffer();
        handlePost(_runLoopPostRequest);
        redirect(_runLoopGetRequest->getURI());
    });
    _ws->on(_runLoopGetRequest->getURI(), [this]() {
        resetBuffer();
        handleGet(_runLoopGetRequest);
    });
    _ws->on(_emailPostRequest->getURI(), [this]() {
        resetBuffer();
        handlePost(_emailPostRequest);
        redirect(_emailGetRequest->getURI());
    });
    _ws->on(_emailGetRequest->getURI(), [this]() {
        resetBuffer();
        handleGet(_emailGetRequest);
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