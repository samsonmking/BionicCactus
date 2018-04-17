#include <web/runloop/RunLoopFormTemplate.hpp>

using namespace Web;

RunLoopFormTemplate::RunLoopFormTemplate(const char *postUri, SoilRunLoop &runLoop) :
_postUri(postUri), _runLoop(runLoop) {

}

int RunLoopFormTemplate::getForm(char *out, size_t len) {
    char *pos = out;
    char *end = out + len;
    const char *formOpening = R"(<Form action="%s" method="post">)";
    const char *dispersionMin = R"(<p>Dispersion Time<br><input type = "text" name = "%s" value = "%i"> min</p>)";
    const char *hrsAtMoisture = R"(<p>Time At Moisture<br><input type = "text" name = "%s" value = "%i"> hrs</p>)";
    const char *hrsDry = R"(<p>Dry Time<br><input type = "text" name = "%s" value = "%i"> hrs</p>)";
    const char *maxDispense = R"(<p>Max Dispense<br><input type = "text" name = "%s" value = "%i"> mL</p>)";
    const char *mlPerPercent = R"(<p>mL Per Percent<br><input type = "text" name = "%s" value = "%i"> mL</p>)";
    const char *setPoint = R"(<p>Set Point<br><input type = "text" name = "%s" value = "%i"> percent</p>)";
    const char *tolerance = R"(<p>Tolerance<br><input type = "text" name = "%s" value = "%i"> percent</p>)";
    const char *formClosing = R"(<input type="submit" value="Submit"></Form>)";
    
    pos += snprintf(pos, end - pos, formOpening, _postUri);
    pos += snprintf(pos, end - pos, dispersionMin, CONST_DISPERSION_MIN, _runLoop.getDispersionMin());
    pos += snprintf(pos, end - pos, hrsAtMoisture, CONST_HRS_AT_MOISTURE, _runLoop.getHrsAtMoisture());
    pos += snprintf(pos, end - pos, hrsAtMoisture, CONST_HRS_AT_MOISTURE, _runLoop.getHrsAtMoisture());
    pos += snprintf(pos, end - pos, hrsDry, CONST_HRS_DRY, _runLoop.getHrsDry());
    pos += snprintf(pos, end - pos, maxDispense, CONST_MAX_DISPENSE, _runLoop.getMaxDispense());
    pos += snprintf(pos, end - pos, mlPerPercent, CONST_ML_PER_PERCENT, _runLoop.getmlPerPercent());
    pos += snprintf(pos, end - pos, setPoint, CONST_SET_POINT, _runLoop.getSetPoint());
    pos += snprintf(pos, end - pos, tolerance, CONST_TOLERANCE, _runLoop.getTolerance());
    pos += snprintf(pos, end - pos, formClosing);

    return pos - out;
}