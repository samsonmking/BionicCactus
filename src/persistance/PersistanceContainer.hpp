#ifndef PERSISTANCE_CONTAINER_H
#define PERSISTANCE_CONTAINER_H

#include <persistance/FileHandler.hpp>
#include <FS.h>

namespace Persistance {

    class PersistanceContainer {
        public:
            PersistanceContainer(FileHandler *handlers[], int len);
    };
}

#endif