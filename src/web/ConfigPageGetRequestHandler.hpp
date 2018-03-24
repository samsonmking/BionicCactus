#ifndef CONFIG_GET_REQUEST_H
#define CONFIG_GET_REQUEST_H

#include <web/GetRequestHandler.hpp>
#include <web/SettingsFormTemplate.hpp>
#include <Arduino.h>

class ConfigPageGetRequestHandler : public GetRequestHandler {
    public:
        ConfigPageGetRequestHandler(const char *uri, const char *title, const char *h1, SettingsFormTemplate *formTemplate);
        inline virtual const char *getURI() override {
            return _uri;
        };
        virtual void getHTML(char *out) override;
    private:
        const char *_uri;
        const char *_title;
        const char *_h1;
        SettingsFormTemplate *_formTemplate;
        void formatHeader(char *out);
        void formatForm(char *out);
        void formatFooter(char *out);
};

#endif