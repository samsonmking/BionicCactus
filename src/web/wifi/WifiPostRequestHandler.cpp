#include "web/wifi/WifiPostRequestHandler.hpp"

using namespace Web;

WifiPostRequestHandler::WifiPostRequestHandler(const char *uri, WifiFileHandler &wifi) :
_uri(uri), _wifi(wifi) {

}

const char *WifiPostRequestHandler::getURI() {
    return _uri;
}

void WifiPostRequestHandler::setVals(PostParameter params[], int numParams) {
    for(int i = 0; i < numParams; i++) {
        if (strcmp(params[i].key, CONST_SSID) == 0) {
            _wifi.setSSID(params[i].value);
            continue;
        }
        else if(strcmp(params[i].key, CONST_PASSWORD) == 0) {
            _wifi.setPassword(params[i].value);
            continue;
        }
        else if(strcmp(params[i].key, CONST_HOSTNAME) == 0) {
            _wifi.setHostname(params[i].value);
            continue;
        }
    }
    _wifi.save();
    
}
