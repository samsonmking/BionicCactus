#ifndef PERI_PUMP_FORM_TEMPLATE_H
#define PERI_PUMP_FORM_TEMPLATE_H

#include <web/SettingsFormTemplate.hpp>
#include <constants/PumpConstants.hpp>
#include <PeriPump.hpp>
#include <Arduino.h>

class PeriPumpFormTemplate : public SettingsFormTemplate {
public:
    PeriPumpFormTemplate(const char *postUri, PeriPump &pump);
    virtual int getForm(char *out, size_t len) override;
private:
    const char *_postUri;
    PeriPump &_pump;
};

#endif