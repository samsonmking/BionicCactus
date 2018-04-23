#ifndef RUNLOOP_FORM_TEMPLATE_H
#define RUNLOOP_FORM_TEMPLATE_H

#include "web/SettingsFormTemplate.hpp"
#include "constants/RunLoopConstants.hpp"
#include "SoilRunLoop.hpp"
#include <Arduino.h>

using namespace Constants;

namespace Web {

    class RunLoopFormTemplate : public SettingsFormTemplate {
        public:
            RunLoopFormTemplate(const char *postUri, SoilRunLoop &runLoop);
            virtual int getForm(char *out, size_t len) override;
        private:
            const char *_postUri;
            SoilRunLoop &_runLoop;
    };

}

#endif