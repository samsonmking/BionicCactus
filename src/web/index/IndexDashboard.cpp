#include "IndexDashboard.hpp"

namespace Web {

    IndexDashboard::IndexDashboard(ValuesDashboardTemplate **templates, int numTemplates) :
    _templates(templates),
    _numTemplates(numTemplates) {

    }

    int IndexDashboard::getDashboard(char* out, size_t len) {
        char* pos = out;
        char* end = out + len;

        pos += snprintf(pos, end - pos, "<h2>Status</h2>");

        for(int i = 0; i < _numTemplates; i++) {            
            pos += _templates[i]->getDashboard(pos, end - pos);
        }

        return pos - out;
    }

}