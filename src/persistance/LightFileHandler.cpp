#include <persistance/LightFileHandler.hpp>

LightFileHandler::LightFileHandler(Light *light) : _light(light) {

}

void LightFileHandler::save() {
    StaticJsonBuffer<CONST_FILE_LENGTH> jsonBuffer;
    auto &lightRoot = jsonBuffer.createObject();
    lightRoot[CONST_BRIGHTNESS] = _light->getBrightness();
    lightRoot[CONST_TIME_ON] = _light->getTimeOn();
    lightRoot[CONST_TIME_OFF] = _light->getTimeOff();
    lightRoot[CONST_LIGHT_ENABLE] = _light->getEnabled();
    auto file = SPIFFS.open(_filePath, "w");
    lightRoot.printTo(file);
    file.close();
}

void LightFileHandler::load() {
    auto file = SPIFFS.open(_filePath, "r");
    if (!file) {
        return;
    }
    StaticJsonBuffer<CONST_FILE_LENGTH> jsonBuffer;
    auto &settingsRoot = jsonBuffer.parseObject(file);
    file.close();
    int brightness = settingsRoot[CONST_BRIGHTNESS];
    _light->setBrightness(brightness);
    const char *timeOn = settingsRoot[CONST_TIME_ON];
    _light->setTimeOn(timeOn);
    const char *timeOff = settingsRoot[CONST_TIME_OFF];
    _light->setTimeOff(timeOff);
    _light->setEnabled(settingsRoot[CONST_LIGHT_ENABLE]);
}
