#include <web/soil/DFSoilPostRequestHandler.hpp>
using namespace Web;

DFSoilPostRequestHandler::DFSoilPostRequestHandler(const char *uri, DFSoil &soil, FileHandler *persistance) :
_uri(uri), _soil(soil), _persistance(persistance) {

}

const char *DFSoilPostRequestHandler::getURI() {
    return _uri;
}

void DFSoilPostRequestHandler::setVals(PostParameter postParams[], int numParams) {
    for (int i = 0; i < numParams; i++) {
        if(strcmp(postParams[i].key, CONST_READING_HIGH) == 0) {
            int high = atoi(postParams[i].value);
            _soil.setHigh(high);
            continue;
        }
        else if(strcmp(postParams[i].key, CONST_READING_LOW) == 0) {
            int low = atoi(postParams[i].value);
            _soil.setLow(low);
        }
    }
    _persistance->save();
}