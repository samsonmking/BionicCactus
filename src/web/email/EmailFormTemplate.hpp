#ifndef EMAIL_FORM_TEMPLATE_H
#define EMAIL_FORM_TEMPLATE_H

#include "web/SettingsFormTemplate.hpp"
#include "email/EmailConfig.hpp"
#include "constants/EmailConstants.hpp"
#include <Arduino.h>

namespace Web {

    class EmailFormTemplate : public SettingsFormTemplate {
        public:
            EmailFormTemplate(const char* postUri, Email::EmailConfig& config);
            virtual int getForm(char* out, size_t len) override;
        private:
            const char *_postUri;
            Email::EmailConfig& _config;
    };

}

#endif