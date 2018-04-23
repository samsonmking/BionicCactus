#ifndef LIGHT_FORM_TEMPLATE_H
#define LIGHT_FORM_TEMPLATE_H

#include "web/SettingsFormTemplate.hpp"
#include "Light.hpp"
#include <Arduino.h>

namespace Web {

    class LightFormTemplate : public SettingsFormTemplate {
    public:
        LightFormTemplate(const char *postUri, Light *light);
        virtual int getForm(char *out, size_t len) override;
    private:
        const char *_postUri;
        Light *_light;
    }; 

}

#endif