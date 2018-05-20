#ifndef BOTTLE_DASHBOARD_H
#define BOTTLE_DASHBOARD_H

#include "web/ValuesDashboardTemplate.hpp"
#include "sensors/bottle/LIDARBottle.hpp"

namespace Web {

    class BottleDashboardTemplate : public ValuesDashboardTemplate {
        public:
            BottleDashboardTemplate(Sensors::Bottle::LidarBottle& bottle);
            virtual int getDashboard(char* out, size_t len) override;
        private:
            Sensors::Bottle::LidarBottle& _bottle;
    };

}

#endif