#include "web/index/IndexConnectedGetRequestHandler.hpp"

using namespace Web;

IndexConnectedGetRequestHandler::IndexConnectedGetRequestHandler(Header &header, 
const char *lightUri, 
const char *pumpUri, 
const char *soilUri,
const char *runLoopUri,
const char *emailUri,
const char *bottleUri,
const char *wifiUri,
IndexDashboard& dashboard) : 
_header(header),
_lightUri(lightUri),
_pumpUri(pumpUri),
_soilUri(soilUri),
_runLoopUri(runLoopUri),
_emailUri(emailUri),
_bottleUri(bottleUri),
_wifiUri(wifiUri),
_dashboard(dashboard) {

}

const char *getURI() {
    return "/";
}

void IndexConnectedGetRequestHandler::getHTML(char *out, size_t len) {
    char *pos = out;
    char *end = out + len;
    pos += _header.getHeader(pos, end - pos);
    pos += _dashboard.getDashboard(pos, end - pos);
    pos += snprintf(pos, end - pos, R"(<h2>Preferences</h2><ul>)");
    pos += snprintf(pos, end - pos, R"(<li><a href="%s">Watering System</a></li>)", _runLoopUri);
    pos += snprintf(pos, end - pos, R"(<li><a href="%s">Light</a></li>)", _lightUri);
    pos += snprintf(pos, end - pos, R"(<li><a href="%s">Email Notifications</a></li></ul>)", _emailUri);
    pos += snprintf(pos, end - pos, R"(<h2>Calibration</h2><ul>)");
    pos += snprintf(pos, end - pos, R"(<li><a href="%s">Pump Setup</a></li>)", _pumpUri);
    pos += snprintf(pos, end - pos, R"(<li><a href="%s">Soil Moisture Sensor</a></li>)", _soilUri);
    pos += snprintf(pos, end - pos, R"(<li><a href="%s">Water Level Sensor</a></li></ul>)", _bottleUri);
    pos += snprintf(pos, end - pos, R"(<h2>System</h2><ul>)");
    pos += snprintf(pos, end - pos, R"(<li><a href="%s">Wifi</a></li></ul>)", _wifiUri);
    pos += snprintf(pos, end - pos, R"(</ul></body></html>)");
}
