#ifndef PERI_PUMP_FORM_TEMPLATE_H
#define PERI_PUMP_FORM_TEMPLATE_H

#include "web/SettingsFormTemplate.hpp"
#include "constants/PumpConstants.hpp"
#include "sensors/pump/PeriPump.hpp"
#include <Arduino.h>

using namespace Constants;
using namespace Sensors::Pump;

namespace Web {

    class PeriPumpFormTemplate : public SettingsFormTemplate {
    public:
        PeriPumpFormTemplate(const char *postUri, PeriPump &pump);
        virtual int getForm(char *out, size_t len) override;
    private:
        const char *_postUri;
        PeriPump &_pump;
    };
    
}

#endif