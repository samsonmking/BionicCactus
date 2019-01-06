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
                                <div style="position: absolute; width: %d%%; height: 30px; border-right: 4px solid black;"></div>
                            </div>
			            </div>		
		            </div>
		            <div style="font-weight: normal;"> %d%% (actual) / %d%% (set) </div>
	            </div>)";

        const int padding = 7;
        int percent = _sensor.getPercent();
        pos += snprintf(pos, end - pos, progressBar, percent, percent, _runLoop.getSetPoint());

        return pos - out;
    }

}
