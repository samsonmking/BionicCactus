#ifndef LIGHT_FILE_HANDLER_H
#define LIGHT_FILE_HANDLER_H

#include "persistance/FileHandler.hpp"
#include "Light.hpp"
#include "ArduinoJson.h"
#include "constants/LightConstants.hpp"
#include "FS.h"

using namespace Constants;

class LightFileHandler : public FileHandler {
public:
    LightFileHandler(Light *light);
    virtual void save() override;
    virtual void load() override;
private:
    const char *_filePath = "/light.json";
    static const size_t CONST_FILE_LENGTH = 200;
    Light *_light;
};

#endif