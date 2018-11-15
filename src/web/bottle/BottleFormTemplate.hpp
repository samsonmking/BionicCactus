#ifndef BOTTLE_FORM_TEMPLATE_H
#define BOTTLE_FORM_TEMPLATE_H

#include "web/SettingsFormTemplate.hpp"
#include "constants/BottleConstants.hpp"
#include "sensors/scale_bottle/Bottle.hpp"
#include <Arduino.h>

using namespace Constants;
using namespace Sensors::Bottle;

namespace Web {

    class BottleFormTemplate : public SettingsFormTemplate {
        public:
            BottleFormTemplate(const char *postUri, Bottle &bottle);
            int getForm(char* out, size_t len) override;
        private:
            const char *_postUri;
            Bottle &_bottle;
    };

}

#endif
