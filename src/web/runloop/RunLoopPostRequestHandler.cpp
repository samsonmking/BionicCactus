#include <web/runloop/RunLoopPostRequestHandler.hpp>

using namespace Web;

RunLoopPostRequestHandler::RunLoopPostRequestHandler(const char *uri, SoilRunLoop &runLoop, FileHandler *persistance) :
_uri(uri), _runLoop(runLoop), _persistance(persistance) {

}

void RunLoopPostRequestHandler::setVals(PostParameter postParams[], int num) {
    bool enabled = false;
    for (int i = 0; i < num; i++) {
        if(strcmp(postParams[i].key, CONST_DISPERSION_MIN) == 0) {
            int dispersionMin = atoi(postParams[i].value);
            _runLoop.setDispersionMin(dispersionMin);
            continue;
        }
        else if (strcmp(postParams[i].key, CONST_HRS_AT_MOISTURE) == 0) {
            int hrsAtMoisture = atoi(postParams[i].value);
            _runLoop.setHrsAtMoisture(hrsAtMoisture);
            continue;
        }
        else if (strcmp(postParams[i].key, CONST_HRS_DRY) == 0) {
            int hrsDry = atoi(postParams[i].value);
            _runLoop.setHrsDry(hrsDry);
            continue;
        }
        else if (strcmp(postParams[i].key, CONST_MAX_DISPENSE) == 0) {
            int maxDisp = atoi(postParams[i].value);
            _runLoop.setMaxDispense(maxDisp);
            continue;
        }
        else if (strcmp(postParams[i].key, CONST_ML_PER_PERCENT) == 0) {
            int mlPerPercent = atoi(postParams[i].value);
            _runLoop.setmlPerPercent(mlPerPercent);
            continue;
        }
        else if (strcmp(postParams[i].key, CONST_SET_POINT) == 0) {
            int setPoint = atoi(postParams[i].value);
            _runLoop.setSetPoint(setPoint);
            continue;
        }
        else if(strcmp(postParams[i].key, CONST_TOLERANCE) == 0) {
            int tolerance = atoi(postParams[i].value);
            _runLoop.setTolerance(tolerance);
            continue;
        }
        else if(strcmp(postParams[i].key, CONST_ENABLE_RUNLOOP) == 0) {
            enabled=true;
            continue;
        }
    }

    _runLoop.setEnabled(enabled);
    _persistance->save();
}

const char *RunLoopPostRequestHandler::getURI() {
    return _uri;
}
