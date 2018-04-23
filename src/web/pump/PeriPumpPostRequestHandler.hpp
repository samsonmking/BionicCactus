#ifndef PUMP_POST_REQUEST_H
#define PUMP_POST_REQUEST_H

#include "web/PostRequestHandler.hpp"
#include "constants/PumpConstants.hpp"
#include "sensors/pump/PeriPump.hpp"
#include "persistance/FileHandler.hpp"
#include <Arduino.h>

using namespace Constants;
using namespace Sensors::Pump;

namespace Web {

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

}

#endif