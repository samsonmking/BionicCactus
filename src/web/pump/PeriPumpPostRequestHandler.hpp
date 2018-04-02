#ifndef PUMP_POST_REQUEST_H
#define PUMP_POST_REQUEST_H

#include <web/PostRequestHandler.hpp>
#include <constants/PumpConstants.hpp>
#include <PeriPump.hpp>
#include <Arduino.h>
#include <persistance/FileHandler.hpp>

class PeriPumpPostRequestHandler : public PostRequestHandler {
public:
    PeriPumpPostRequestHandler(const char *uri, PeriPump &pump, FileHandler *persistance);
    virtual void setVals(PostParameter postParams[], int numParams) override;
    virtual const char *getURI() override;
private:
    const char *_uri;
    PeriPump &_pump;
    FileHandler *_persistance;
};

#endif