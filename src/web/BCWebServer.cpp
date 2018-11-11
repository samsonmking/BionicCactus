#include <web/BCWebServer.hpp>

BCWebServer::BCWebServer(ESP8266WebServer *ws,
GetRequestHandler &indexGetRequest, 
PostRequestHandler &wifiPostRequest,
GetRequestHandler &wifiGetRequest,
WifiController &wifiController) : 
_ws(ws),
_getIndex(indexGetRequest),
_wifiPostRequest(wifiPostRequest),
_wifiGetRequest(wifiGetRequest),
_wifiController(wifiController){
    resetBuffer();
}

void BCWebServer::contributeGetRequest(GetRequestHandler &getRequest) {
    _ws->on(getRequest.getURI(), [this, &getRequest]() {
            resetBuffer();
            handleGet(getRequest);
        });
}

void BCWebServer::contributePostRequest(PostRequestHandler &postRequest, const char *redirectUri) {
    _ws->on(postRequest.getURI(), [this, &postRequest, redirectUri]() {
            resetBuffer();
            handlePost(postRequest);
            redirect(redirectUri);
        });
}

void BCWebServer::setupServer() {
    // Configure Endpoints
    _ws->on(_getIndex.getURI(), [this]() {
        resetBuffer();
        if (_wifiController.isConnected()) {
            handleGet(_getIndex);
        } else {
            redirect(_wifiGetRequest.getURI());
        }
    });
    _ws->on(_wifiGetRequest.getURI(), [this]() {
        resetBuffer();
        handleGet(_wifiGetRequest);
    });
    _ws->on(_wifiPostRequest.getURI(), [this]() {
        resetBuffer();
        handlePost(_wifiPostRequest);
        _ws->send(200, "text/plain", "WiFi will disconnect in 5 seconds. Refresh and check connection.");
        _wifiController.clientMode();
    });
    _ws->begin();
}

void BCWebServer::handleGet(GetRequestHandler &request) {
    request.getHTML(_buffer, sizeof(_buffer));
    _ws->send(200, "text/html", _buffer);
}

void BCWebServer::handlePost(PostRequestHandler &request) {
    int args = _ws->args();
    for(int i = 0; i < args; i++) {
        strcpy(_postParams[i].key, _ws->argName(i).c_str());
        strcpy(_postParams[i].value, _ws->arg(i).c_str());
    }
    request.setVals(_postParams, args);
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
