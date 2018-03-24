#ifndef GET_REQUEST_HANDLER_H
#define GET_REQUEST_HANDLER_H

#include <web/WebRequestHandler.hpp>

class GetRequestHandler : public WebRequestHandler {
public:
    virtual void getHTML(char *out) = 0;
};

#endif