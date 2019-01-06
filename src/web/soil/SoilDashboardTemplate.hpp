#ifndef SOIL_DASHBOARD_H
#define SOIL_DASHBOARD_H

#include "web/ValuesDashboardTemplate.hpp"
#include "sensors/soil/SoilSensor.hpp"
#include "SoilRunLoop.hpp"

namespace Web {

    class SoilDashboardTemplate : public ValuesDashboardTemplate {
        public:
            SoilDashboardTemplate(Sensors::Soil::SoilSensor& sensor, SoilRunLoop& runLoop);
            virtual int getDashboard(char* out, size_t len) override;
        private:
            Sensors::Soil::SoilSensor& _sensor;
            SoilRunLoop& _runLoop;
    };

}

#endif