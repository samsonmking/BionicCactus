#ifndef SETTINGS_FORM_TEMPLATE_H
#define SETTINGS_FORM_TEMPLATE_H

#include <Arduino.h>

class SettingsFormTemplate {
public:
    virtual int getForm(char *out, size_t len) = 0;
};

#endif