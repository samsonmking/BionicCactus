#ifndef BOTTLE_POST_REQUEST_H
#define BOTTLE_POST_REQUEST_H

#include "web/PostRequestHandler.hpp"
#include "constants/BottleConstants.hpp"
#include "persistance/BottleFileHandler.hpp"
#include "sensors/scale_bottle/Bottle.hpp"

using namespace Persistance;
using namespace Sensors::Bottle;
namespace Web {

    class BottlePostRequestHandler : public PostRequestHandler {
        public:
            BottlePostRequestHandler(const char *uri, 
                    BottleFileHandler &persistance,
                    Bottle &bottle);
            void setVals(PostParameter postParams[], int numParams) override;
            const char *getURI() override;
        private:
            const char *_uri;
            BottleFileHandler &_persistance;
            Bottle &_bottle;
    };

}

#endif
