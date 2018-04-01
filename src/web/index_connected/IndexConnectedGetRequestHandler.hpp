#ifndef INDEX_CONNECTED_H
#define INDEX_CONNECTED_H

#include <Arduino.h>
#include <web/GetRequestHandler.hpp>
#include <web/Header.hpp>

class IndexConnectedGetRequestHandler : public GetRequestHandler {
public:
    IndexConnectedGetRequestHandler(Header &header, const char *lightUri);
    inline virtual const char *getURI() override {
            return "/";
    };
    virtual void getHTML(char *out, size_t len) override;
private:
    Header _header;
    const char *_lightUri;
};

#endif