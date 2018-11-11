#include "web/bottle/BottleDashboardTemplate.hpp"

using namespace Sensors::Bottle;

namespace Web {

    BottleDashboardTemplate::BottleDashboardTemplate(Bottle& bottle) :
    _bottle(bottle) {

    }

    int BottleDashboardTemplate::getDashboard(char* out, size_t len) {
        char* pos = out;
        char* end = out + len;

        const char* tableOpening = R"(<table><tr>)";
        const char* moisture = R"(<td width="200">Bottle Level</td><td>%d percent</td>)";
        const char* tableClosing = R"(</tr></table>)";

        pos += snprintf(pos, end - pos, tableOpening);
        pos += snprintf(pos, end - pos, moisture, _bottle.getPercent());
        pos += snprintf(pos, end - pos, tableClosing);

        return pos - out;
    }

}
