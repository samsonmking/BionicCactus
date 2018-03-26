#ifndef POST_REQUEST_HANDLER_H
#define POST_REQUEST_HANDLER_H

#include <web/WebRequestHandler.hpp>

typedef struct {
    char key[100];
    char value[100];
} PostParameter;

class PostRequestHandler : public WebRequestHandler {
public:
    virtual void setVals(PostParameter postParams[], int numParams) = 0;
};

#endif