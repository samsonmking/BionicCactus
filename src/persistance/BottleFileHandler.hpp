#ifndef BOTTLE_FILE_HANDLER_H
#define BOTTLE_FILE_HANDLER_H

#include "FileHandler.hpp"
#include "sensors/scale_bottle/Bottle.hpp"
#include "ArduinoJson.h"
#include "constants/BottleConstants.hpp"
#include "FS.h"

using namespace Constants;
using namespace Sensors::Bottle;

namespace Persistance {

    class BottleFileHandler : public FileHandler {
        public:
            BottleFileHandler(Bottle &bottle);
            void save() override;
            void load() override;
        private:
            const char *_filePath = "/bottle.json";
            static const size_t CONST_FILE_LENGTH = 300;
            Bottle &_bottle;
    };

}

#endif
