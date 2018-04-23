#include "web/light/LightPostRequestHandler.hpp"

using namespace Web;

LightPostRequestHandler::LightPostRequestHandler(const char *uri, Light *light, FileHandler *persistance) : 
_uri(uri), _light(light), _persistance(persistance) {

}

const char *LightPostRequestHandler::getURI() {
    return _uri;
}

void LightPostRequestHandler::setVals(PostParameter params[], int numParams) {
    for(int i = 0; i < numParams; i++) {
        if (strcmp(params[i].key, CONST_BRIGHTNESS) == 0) {
            int brightness = atoi(params[i].value);
            _light->setBrightness(brightness);
            continue;
        }
        else if (strcmp(params[i].key, CONST_TIME_ON) == 0){
            _light->setTimeOn(params[i].value);
            continue;
        }
        else if (strcmp(params[i].key, CONST_TIME_OFF) == 0) {
            _light->setTimeOff(params[i].value);
            continue;
        }
    }
    _persistance->save();
}