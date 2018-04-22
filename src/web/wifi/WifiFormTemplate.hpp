#ifndef WIFI_FORM_TEMPLATE_H
#define WIFI_FORM_TEMPLATE_H

#include "web/SettingsFormTemplate.hpp"
#include "constants/WifiConstants.hpp"
#include "persistance/WifiFileHandler.hpp"
#include <Arduino.h>

using namespace Constants;
using namespace Persistance;

namespace Web {

    class WifiFormTemplate : public SettingsFormTemplate {
        public:
            WifiFormTemplate(const char *postUri, WifiFileHandler &wifi);
            virtual int getForm(char *out, size_t len) override;
        private:
            const char *_postUri;
            WifiFileHandler &_wifi;
    };

}

#endif