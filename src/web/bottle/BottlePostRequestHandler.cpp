#include "BottlePostRequestHandler.hpp"

using namespace Web;

BottlePostRequestHandler::BottlePostRequestHandler(const char *uri,
        BottleFileHandler &persistance,
        Bottle &bottle) : 
    _uri(uri),
    _persistance(persistance),
    _bottle(bottle) {
}

void BottlePostRequestHandler::setVals(PostParameter postParams[], int numParams) {
    for(int i = 0; i < numParams; i++) {
        if(strcmp(postParams[i].key, CONST_EMPTY) == 0) {
            long empty = atol(postParams[i].value);
            _bottle.setEmpty(empty);
            continue;
        } else if(strcmp(postParams[i].key, CONST_FULL) == 0) {
            long full = atol(postParams[i].value);
            _bottle.setFull(full);
            continue;
        }
    }
    _persistance.save();
}

const char *BottlePostRequestHandler::getURI() {
    return _uri;
}
