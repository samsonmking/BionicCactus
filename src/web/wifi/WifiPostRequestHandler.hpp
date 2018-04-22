#ifndef WIFI_POST_REQUEST_H
#define WIFI_POST_REQUEST_H

#include "web/PostRequestHandler.hpp"
#include "constants/WifiConstants.hpp"
#include "persistance/WifiFileHandler.hpp"
#include "Arduino.h"

using namespace Constants;
using namespace Persistance;

namespace Web {

    class WifiPostRequestHandler : public PostRequestHandler {
        public:
            WifiPostRequestHandler(const char *uri, WifiFileHandler &wifi);
            virtual void setVals(PostParameter postParams[], int numParams) override;
            virtual const char *getURI() override;
        private:
            const char *_uri;
            WifiFileHandler &_wifi;
    };

}

#endif