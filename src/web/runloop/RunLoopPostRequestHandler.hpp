#ifndef RUNLOOP_POST_REQUEST_H
#define RUNLOOP_POST_REQUEST_H

#include <web/PostRequestHandler.hpp>
#include <constants/RunLoopConstants.hpp>
#include <SoilRunLoop.hpp>
#include <Arduino.h>
#include <persistance/FileHandler.hpp>

using namespace Constants;

namespace Web {

    class RunLoopPostRequestHandler : public PostRequestHandler {
        public:
            RunLoopPostRequestHandler(const char *uri, SoilRunLoop &runLoop, FileHandler *persistance);
            virtual void setVals(PostParameter postParams[], int numParams) override;
            virtual const char *getURI() override;
        private:
            const char *_uri;
            SoilRunLoop &_runLoop;
            FileHandler *_persistance;
    };

}

#endif