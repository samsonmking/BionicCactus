#include "web/soil/DFSoilFormTemplate.hpp"

using namespace Web;

DFSoilFormTemplate::DFSoilFormTemplate(const char *postUri, DFSoil &soil) : _postUri(postUri), _soil(soil) {

}

int DFSoilFormTemplate::getForm(char *out, size_t len) {
    char *pos = out;
    char *end = out + len;
    const char *formOpening = R"(<Form action="%s" method="post">)";
    const char *highInput = R"(<p>High Reading<br><input type = "text" name = "%s" value = "%d"></p>)";
    const char *lowInput = R"(<p>Low Reading<br><input type = "text" name = "%s" value = "%d"></p>)";
    const char *formClosing = R"(<input type="submit" value="Submit"></Form>)";
    pos += snprintf(pos, end - pos, formOpening, _postUri);
    pos += snprintf(pos, end - pos, highInput, CONST_READING_HIGH, _soil.getHigh());
    pos += snprintf(pos, end - pos, lowInput, CONST_READING_LOW, _soil.getLow());
    pos += snprintf(pos, end - pos, formClosing);
    return pos - out;
}