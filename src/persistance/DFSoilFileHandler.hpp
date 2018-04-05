#ifndef DFSOIL_FILE_HANDLER_H
#define DFSOIL_FILE_HANDLER_H

#include <persistance/FileHandler.hpp>
#include <DFSoil.hpp>
#include <ArduinoJson.h>
#include <constants/DFSoilConstants.hpp>
#include <FS.h>

using namespace Constants;

namespace Persistance {

    class DFSoilFileHandler : public FileHandler {
    public:
        DFSoilFileHandler(DFSoil &soil);
        virtual void save() override;
        virtual void load() override;
    private:
        const char *_filePath = "/soil.json";
        static const size_t CONST_FILE_LENGTH = 200;
        DFSoil &_soil;
    };

};

#endif