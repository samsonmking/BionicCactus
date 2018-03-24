#ifndef WEB_REQUEST_HANDLER_H
#define WEB_REQUEST_HANDLER_H

class WebRequestHandler {
public:
    virtual const char *getURI() = 0;
};

#endif