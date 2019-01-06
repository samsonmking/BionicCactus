#include "web/bottle/BottleDashboardTemplate.hpp"

using namespace Sensors::Bottle;

namespace Web {

    BottleDashboardTemplate::BottleDashboardTemplate(Bottle& bottle) :
    _bottle(bottle) {

    }

    int BottleDashboardTemplate::getDashboard(char* out, size_t len) {
        char* pos = out;
        char* end = out + len;

        const char* progressBar = R"(
            <div class="progressLabel">
                Water Bottle Level
                <div class="progressOuter">
                    <div class="progressInner" style="width: %d%%; background-color: %s;">%d %%</div>
                </div>
            </div>)";

        int percent = _bottle.getPercent();
        const char* color = (percent < 30) ? "red" : "blue";
        pos += snprintf(pos, end - pos, progressBar, percent, color, percent);

        return pos - out;
    }

}
