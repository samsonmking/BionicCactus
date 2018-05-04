#ifndef SOIL_DASHBOARD_H
#define SOIL_DASHBOARD_H

#include "web/ValuesDashboardTemplate.hpp"
#include "sensors/soil/SoilSensor.hpp"

namespace Web {

    class SoilDashboardTemplate : public ValuesDashboardTemplate {
        public:
            SoilDashboardTemplate(Sensors::Soil::SoilSensor& sensor);
            virtual int getDashboard(char* out, size_t len) override;
        private:
            Sensors::Soil::SoilSensor& _sensor;
    };

}

#endif