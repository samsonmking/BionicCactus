#ifndef RUNLOOP_FILE_HANDLER_H
#define RUNLOOP_FILE_HANDLER_H

#include <persistance/FileHandler.hpp>
#include <SoilRunLoop.hpp>
#include <ArduinoJson.h>
#include <constants/RunLoopConstants.hpp>
#include <FS.h>

using namespace Constants;

namespace Persistance {

class RunLoopFileHandler : public FileHandler {
    public:
        RunLoopFileHandler(SoilRunLoop &runLoop);
        virtual void save() override;
        virtual void load() override;
    private:
        const char *_filePath = "/runloop.json";
        static const size_t CONST_FILE_LENGTH = 500;
        SoilRunLoop &_runLoop;    
};

}

#endif
