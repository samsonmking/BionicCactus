#include "web/soil/SoilDashboardTemplate.hpp"

using namespace Sensors::Soil;

namespace Web {

    SoilDashboardTemplate::SoilDashboardTemplate(SoilSensor& sensor, SoilRunLoop& runLoop) :
    _sensor(sensor),
    _runLoop(runLoop) {

    }

    int SoilDashboardTemplate::getDashboard(char* out, size_t len) {
        char* pos = out;
        char* end = out + len; 

        const char* progressBar = R"(
            	<div class="progressLabel">Moisture Level
		            <div class="progressOuter" style="background-color: blue; position: relative;">	
			            <div class="progressInner" style="width: 160px; background-color: green;">
                            <div class="progressInner" style="width: 40px; background-color: red;">
                                <div style="position: absolute; width: %d%%; height: 30px; border-right: 4px solid white;"></div>
                            </div>
			            </div>		
		            </div>
		           <div style="text-align: center; width:200px;">%d%% | <span style="font-size: 0.7em;">%d%%</span> - %s</div>
	            </div>)";

        const int padding = 7;
        int percent = _sensor.getPercent();
        const char* description = "Dry";
        if(percent > 20) {
            description = "Moist";
        } else if (percent > 80) {
            description = "Wet";
        }
        pos += snprintf(pos, end - pos, progressBar, percent, percent, _runLoop.getSetPoint(), description);

        return pos - out;
    }

}
