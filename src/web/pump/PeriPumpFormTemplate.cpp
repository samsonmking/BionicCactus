#include "web/pump/PeriPumpFormTemplate.hpp"

using namespace Web;

PeriPumpFormTemplate::PeriPumpFormTemplate(const char *postUri, PeriPump &pump) :
_postUri(postUri), _pump(pump) {

}

int PeriPumpFormTemplate::getForm(char *out, size_t len) {
    char *pos = out;
    char *end = out + len;
    const char *formOpening = R"(<Form action="%s" method="post">)";
    const char *flowRate = R"(<p>Flow Rate (ml / s)<br><input type = "text" name = "%s" value = "%f"></p>)";
    const char *formClosing = R"(<input type="submit" value="Submit"></Form>)";
    pos += snprintf(pos, end - pos, formOpening, _postUri);
    pos += snprintf(pos, end - pos, flowRate, CONST_FLOWRATE, _pump.getFlowRate());
    pos += snprintf(pos, end - pos, formClosing);
    return pos - out;
}