#include <persistance/DFSoilFileHandler.hpp>
using namespace Persistance;

DFSoilFileHandler::DFSoilFileHandler(DFSoil &soil) : _soil(soil) {

}

void DFSoilFileHandler::save() {
    StaticJsonBuffer<CONST_FILE_LENGTH> jsonBuffer;
    auto &soilRoot = jsonBuffer.createObject();
    soilRoot[CONST_READING_HIGH] = _soil.getHigh();
    soilRoot[CONST_READING_LOW] = _soil.getLow();
    auto file = SPIFFS.open(_filePath, "w");
    soilRoot.printTo(file);
    file.close();
}

void DFSoilFileHandler::load() {
    auto file = SPIFFS.open(_filePath, "r");
    if (!file) {
        return;
    }
    StaticJsonBuffer<CONST_FILE_LENGTH> jsonBuffer;
    auto &settingsRoot = jsonBuffer.parseObject(file);
    file.close();
    int high = settingsRoot[CONST_READING_HIGH];
    _soil.setHigh(high);
    int low = settingsRoot[CONST_READING_LOW];
    _soil.setLow(low);
}