#include "BottleFileHandler.hpp"

using namespace Persistance;

BottleFileHandler::BottleFileHandler(Bottle &bottle) : _bottle(bottle) {
}

void BottleFileHandler::save() {
    StaticJsonBuffer<CONST_FILE_LENGTH> jsonBuffer;
    auto &bottleRoot = jsonBuffer.createObject();
    bottleRoot[CONST_EMPTY] = _bottle.getEmpty();
    bottleRoot[CONST_FULL] = _bottle.getFull();
    auto file = SPIFFS.open(_filePath, "w");
    bottleRoot.printTo(file);
    file.close();
}

void BottleFileHandler::load() {
    auto file = SPIFFS.open(_filePath, "r");
    if (!file) {
        return;
    }
    StaticJsonBuffer<CONST_FILE_LENGTH>jsonBuffer;
    auto &settingsRoot = jsonBuffer.parseObject(file);
    file.close();
    long empty = settingsRoot[CONST_EMPTY];
    _bottle.setEmpty(empty);
    long full = settingsRoot[CONST_FULL];
    _bottle.setFull(full);
}
