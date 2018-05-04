#ifndef INDEX_DASHBOARD_H
#define INDEX_DASHBOARD_H

#include "web/ValuesDashboardTemplate.hpp"

namespace Web {

    class IndexDashboard {
        public:
            IndexDashboard(ValuesDashboardTemplate **templates, int numTemplates);
            int getDashboard(char* out, size_t len);
        private:
            ValuesDashboardTemplate **_templates;
            int _numTemplates;
    };

}

#endif