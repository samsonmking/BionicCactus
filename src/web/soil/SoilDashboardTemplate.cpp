#include "web/soil/SoilDashboardTemplate.hpp"

using namespace Sensors::Soil;

namespace Web {

    SoilDashboardTemplate::SoilDashboardTemplate(SoilSensor& sensor) :
    _sensor(sensor) {

    }

    int SoilDashboardTemplate::getDashboard(char* out, size_t len) {
        char* pos = out;
        char* end = out + len; 

        const char* tableOpening = R"(<table><tr>)";
        const char* moisture = R"(<td width="200">Moisture Reading</td><td>%d percent</td>)";
        const char* tableClosing = R"(</tr></table>)";

        pos += snprintf(pos, end - pos, tableOpening);
        pos += snprintf(pos, end - pos, moisture, _sensor.getPercent());
        pos += snprintf(pos, end - pos, tableClosing);

        return pos - out;
    }

}