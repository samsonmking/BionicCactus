#include <web/light/LightPostRequestHandler.hpp>

LightPostRequestHandler::LightPostRequestHandler(const char *uri, Light *light) : _uri(uri), _light(light) {

}

const char *LightPostRequestHandler::getURI() {
    return _uri;
}

void LightPostRequestHandler::setVals(PostParameter params[], int numParams) {
    for(int i = 0; i < numParams; i++) {
        if (strcmp(params[i].key, brightness) == 0) {
            int brightness = atoi(params[i].value);
            _light->setBrightness(brightness);
            continue;
        }
        else if (strcmp(params[i].key, timeOn) == 0){
            _light->setTimeOn(params[i].value);
            continue;
        }
        else if (strcmp(params[i].key, timeOff) == 0) {
            _light->setTimeOff(params[i].value);
            continue;
        }
    }
}