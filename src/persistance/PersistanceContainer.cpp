#include <persistance/PersistanceContainer.hpp>

using namespace Persistance;

PersistanceContainer::PersistanceContainer(FileHandler *handlers[], int len) {
    SPIFFS.begin();
    for (int i = 0; i < len; i++) {
        handlers[i]->load();
    }
}