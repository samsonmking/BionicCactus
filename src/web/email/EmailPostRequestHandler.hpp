#ifndef EMAIL_POST_REQUEST_H
#define EMAIL_POST_REQUEST_H

#include "web/PostRequestHandler.hpp"
#include "constants/EmailConstants.hpp"
#include "persistance/EmailFileHandler.hpp"
#include "email/EmailConfig.hpp"
#include <Arduino.h>

namespace Web {

    class EmailPostRequestHandler : public PostRequestHandler {
        public:
            EmailPostRequestHandler(const char *uri, Persistance::EmailFileHandler& configFile);
            virtual void setVals(PostParameter postParams[], int numParams) override;
            virtual const char* getURI() override;
        private:
            const char* _uri;
            Persistance::EmailFileHandler& _configFile;
    };

}

#endif