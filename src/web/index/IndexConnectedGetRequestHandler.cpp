#include "web/index/IndexConnectedGetRequestHandler.hpp"

using namespace Web;

IndexConnectedGetRequestHandler::IndexConnectedGetRequestHandler(Header &header, 
const char *lightUri, 
const char *pumpUri, 
const char *soilUri,
const char *runLoopUri,
const char *emailUri,
IndexDashboard& dashboard) : 
_header(header),
_lightUri(lightUri),
_pumpUri(pumpUri),
_soilUri(soilUri),
_runLoopUri(runLoopUri),
_emailUri(emailUri),
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
    pos += snprintf(pos, end - pos, R"(<h2>Settings</h2><ul>)");
    pos += snprintf(pos, end - pos, R"(<li><a href="%s">Light</a></li>)", _lightUri);
    pos += snprintf(pos, end - pos, R"(<li><a href="%s">Pump</a></li>)", _pumpUri);
    pos += snprintf(pos, end - pos, R"(<li><a href="%s">Soil</a></li>)", _soilUri);
    pos += snprintf(pos, end - pos, R"(<li><a href="%s">RunLoop</a></li>)", _runLoopUri);
    pos += snprintf(pos, end - pos, R"(<li><a href="%s">Email Notifications</a></li>)", _emailUri);
    pos += snprintf(pos, end - pos, R"(</ul></body></html>)");
}
