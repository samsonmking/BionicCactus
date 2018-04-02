#include <persistance/PeriPumpFileHandler.hpp>

PeriPumpFileHandler::PeriPumpFileHandler(PeriPump &pump) : _pump(pump) {

}

void PeriPumpFileHandler::save() {
    StaticJsonBuffer<CONST_FILE_LENGTH> jsonBuffer;
    auto &pumpRoot = jsonBuffer.createObject();
    pumpRoot[CONST_FLOWRATE] = _pump.getFlowRate();
    auto file = SPIFFS.open(_filePath, "w");
    pumpRoot.printTo(file);
    file.close();
}

void PeriPumpFileHandler::load() {
    auto file = SPIFFS.open(_filePath, "r");
    if (!file) {
        return;
    }
    StaticJsonBuffer<CONST_FILE_LENGTH> jsonBuffer;
    auto &settingsRoot = jsonBuffer.parseObject(file);
    file.close();
    float flowRate = settingsRoot[CONST_FLOWRATE];
    _pump.setFlowRate(flowRate);
}