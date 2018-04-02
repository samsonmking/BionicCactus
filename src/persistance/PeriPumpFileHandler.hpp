#ifndef PERI_PUMP_FILE_HANDLER_H
#define PERI_PUMP_FILE_HANDLER_H

#include <persistance/FileHandler.hpp>
#include <PeriPump.hpp>
#include <ArduinoJson.h>
#include <constants/PumpConstants.hpp>
#include <FS.h>

class PeriPumpFileHandler : public FileHandler {
public:
    PeriPumpFileHandler(PeriPump &pump);
    virtual void save() override;
    virtual void load() override;
private:
    const char *_filePath = "/pump.json";
    static const size_t CONST_FILE_LENGTH = 100;
    PeriPump &_pump;
};

#endif