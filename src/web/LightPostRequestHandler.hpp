#ifndef LIGHT_POST_REQUEST_H
#define LIGHT_POST_REQUEST_H

#include <web/PostRequestHandler.hpp>
#include <constants/LightConstants.hpp>
#include <Light.hpp>
#include <Arduino.h>

class LightPostRequestHandler : public PostRequestHandler {
public:
    LightPostRequestHandler(const char *uri, Light *light);
    virtual void setVals(PostParameter postParams[], int numParams) override;
    virtual const char *getURI() override;
private:
    const char *_uri;
    Light *_light;
};

#endif