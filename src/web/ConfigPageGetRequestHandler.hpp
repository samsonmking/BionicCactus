#ifndef CONFIG_GET_REQUEST_H
#define CONFIG_GET_REQUEST_H

#include <web/GetRequestHandler.hpp>
#include <web/SettingsFormTemplate.hpp>
#include <web/Header.hpp>
#include <Arduino.h>

class ConfigPageGetRequestHandler : public GetRequestHandler {
    public:
        ConfigPageGetRequestHandler(const char *uri, const char *subheading, Header &header, SettingsFormTemplate *formTemplate);
        inline virtual const char *getURI() override {
            return _uri;
        };
        virtual void getHTML(char *out, size_t len) override;
    private:
        const char *_uri;
        Header _header;
        const char *_subheading;
        SettingsFormTemplate *_formTemplate;
        int formatHeader(char *out, size_t len);
        int formatForm(char *out, size_t len);
        int formatFooter(char *out, size_t len);
};

#endif