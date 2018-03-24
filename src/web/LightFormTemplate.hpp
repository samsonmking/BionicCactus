#ifndef LIGHT_FORM_TEMPLATE_H
#define LIGHT_FORM_TEMPLATE_H

#include <web/SettingsFormTemplate.hpp>
#include <Light.hpp>
#include <Arduino.h>

class LightFormTemplate : public SettingsFormTemplate {
public:
    LightFormTemplate(const char *postUri, Light *light);
    virtual void getForm(char *out) override;
private:
    const char *_postUri;
    Light *_light;
}; 

#endif