#ifndef DFSOIL_POST_REQUEST_H
#define DFSOIL_POST_REQUEST_H

#include "web/PostRequestHandler.hpp"
#include "constants/DFSoilConstants.hpp"
#include "DFSoil.hpp"
#include <Arduino.h>
#include "persistance/FileHandler.hpp"

using namespace Constants;

namespace Web {

    class DFSoilPostRequestHandler : public PostRequestHandler {
    public:
        DFSoilPostRequestHandler(const char *uri, DFSoil &soil, FileHandler *persistance);
        virtual void setVals(PostParameter postParams[], int numParams);
        virtual const char *getURI() override;
    private:
        const char *_uri;
        DFSoil &_soil;
        FileHandler *_persistance;
    };
};

#endif