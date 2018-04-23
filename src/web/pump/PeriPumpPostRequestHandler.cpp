#include "web/pump/PeriPumpPostRequestHandler.hpp"

using namespace Web;

PeriPumpPostRequestHandler::PeriPumpPostRequestHandler(const char *uri, PeriPump &pump, FileHandler *persistance) :
_uri(uri), _pump(pump), _persistance(persistance) {
    
}

const char *PeriPumpPostRequestHandler::getURI() {
    return _uri;
}

void PeriPumpPostRequestHandler::setVals(PostParameter postParams[], int numParams) {
    for(int i = 0; i < numParams; i++) {
        if(strcmp(postParams[i].key, CONST_FLOWRATE) == 0) {
            float flowRate = atof(postParams[i].value);
            _pump.setFlowRate(flowRate);
        }
    }
    _persistance->save();
}