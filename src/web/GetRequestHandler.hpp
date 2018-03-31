#ifndef GET_REQUEST_HANDLER_H
#define GET_REQUEST_HANDLER_H

#include <web/WebRequestHandler.hpp>
#include <Arduino.h>

class GetRequestHandler : public WebRequestHandler {
public:
    virtual void getHTML(char *out, size_t len) = 0;
};

#endif