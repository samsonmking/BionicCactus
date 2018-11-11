#ifndef BOTTLE_DASHBOARD_H
#define BOTTLE_DASHBOARD_H

#include "web/ValuesDashboardTemplate.hpp"
#include "sensors/scale_bottle/Bottle.hpp"

namespace Web {

    class BottleDashboardTemplate : public ValuesDashboardTemplate {
        public:
            BottleDashboardTemplate(Sensors::Bottle::Bottle& bottle);
            virtual int getDashboard(char* out, size_t len) override;
        private:
            Sensors::Bottle::Bottle& _bottle;
    };

}

#endif
