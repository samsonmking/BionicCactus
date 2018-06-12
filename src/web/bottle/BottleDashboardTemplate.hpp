#ifndef BOTTLE_DASHBOARD_H
#define BOTTLE_DASHBOARD_H

#include "web/ValuesDashboardTemplate.hpp"
#include "sensors/scale_bottle/ScaleBottle.hpp"

namespace Web {

    class BottleDashboardTemplate : public ValuesDashboardTemplate {
        public:
            BottleDashboardTemplate(Sensors::Bottle::ScaleBottle& bottle);
            virtual int getDashboard(char* out, size_t len) override;
        private:
            Sensors::Bottle::ScaleBottle& _bottle;
    };

}

#endif