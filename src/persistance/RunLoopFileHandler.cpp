#include <persistance/RunLoopFileHandler.hpp>
using namespace Persistance;

RunLoopFileHandler::RunLoopFileHandler(SoilRunLoop &runLoop) : 
_runLoop(runLoop) {

}

void RunLoopFileHandler::save() {
    StaticJsonBuffer<CONST_FILE_LENGTH> jsonBuffer;
    auto &runLoopRoot = jsonBuffer.createObject();
    runLoopRoot[CONST_DISPERSION_MIN] = _runLoop.getDispersionMin();
    runLoopRoot[CONST_HRS_AT_MOISTURE] = _runLoop.getHrsAtMoisture();
    runLoopRoot[CONST_HRS_DRY] = _runLoop.getHrsDry();
    runLoopRoot[CONST_MAX_DISPENSE] = _runLoop.getMaxDispense();
    runLoopRoot[CONST_ML_PER_PERCENT] = _runLoop.getmlPerPercent();
    runLoopRoot[CONST_SET_POINT] = _runLoop.getSetPoint();
    runLoopRoot[CONST_TOLERANCE] = _runLoop.getTolerance();
    runLoopRoot[CONST_ENABLE_RUNLOOP] = _runLoop.getEnabled();
    auto file = SPIFFS.open(_filePath, "w");
    runLoopRoot.printTo(file);
    file.close();
}

void RunLoopFileHandler::load() {
    auto file = SPIFFS.open(_filePath, "r");
    if (!file) {
        return;
    }
    StaticJsonBuffer<CONST_FILE_LENGTH> jsonBuffer;
    auto &settingsRoot = jsonBuffer.parseObject(file);
    file.close();
    int dispersionMin = settingsRoot[CONST_DISPERSION_MIN];
    _runLoop.setDispersionMin(dispersionMin);
    int hrsAtMoisture = settingsRoot[CONST_HRS_AT_MOISTURE];
    _runLoop.setHrsAtMoisture(hrsAtMoisture);
    int hrsDry = settingsRoot[CONST_HRS_DRY];
    _runLoop.setHrsDry(hrsDry);
    int maxDisp = settingsRoot[CONST_MAX_DISPENSE];
    _runLoop.setMaxDispense(maxDisp);
    int mlPerPercent = settingsRoot[CONST_ML_PER_PERCENT];
    _runLoop.setmlPerPercent(mlPerPercent);
    int setPoint = settingsRoot[CONST_SET_POINT];
    _runLoop.setSetPoint(setPoint);
    int tolerance = settingsRoot[CONST_TOLERANCE];
    _runLoop.setTolerance(tolerance);
    _runLoop.setEnabled(settingsRoot[CONST_ENABLE_RUNLOOP]);
}
