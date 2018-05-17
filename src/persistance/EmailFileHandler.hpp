#ifndef EMAIL_FILE_H
#define EMAIL_FILE_H

#include "persistance/FileHandler.hpp"
#include "constants/EmailConstants.hpp"
#include "email/EmailConfig.hpp"
#include "ArduinoJson.h"
#include "FS.h"

namespace Persistance {

    class EmailFileHandler : public FileHandler {
        public:
            EmailFileHandler();
            virtual void save() override;
            virtual void load() override;
            Email::EmailConfig& getConfig();
        private:
            static const int CONST_FILE_LENGTH = 400;
            const char* _filePath = "/email.json";
            Email::EmailConfig _config;
    };

}

#endif