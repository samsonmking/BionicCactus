#ifndef LIGHT_FORM_TEMPLATE_H
#define LIGHT_FORM_TEMPLATE_H

#include "web/SettingsFormTemplate.hpp"
#include "sensors/light/Light.hpp"
#include "constants/LightConstants.hpp"
#include <Arduino.h>

using namespace Sensors::Light;
using namespace Constants;

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
