#include "BottleFormTemplate.hpp"

using namespace Web;

BottleFormTemplate::BottleFormTemplate(const char *postUri, Bottle &bottle) : 
    _postUri(postUri),
    _bottle(bottle) {
}

int BottleFormTemplate::getForm(char *out, size_t len){
    char *pos = out;
    char *end = out + len;
    const char *formOpening = R"(<Form action="%s" method="post">)";
    const char *full = R"(<p>Value When Full<br><input type="text" name="%s" value="%ld"></p>)";
    const char *empty = R"(<p>Value When Empty<br><input type="text" name="%s" value="%ld"></p>)";
    const char *formClosing = R"(<input type="submit" value="Submit"></Form>)";
    const char *tableOpening = R"(<h3>Current Values</h3><table>)";
    const char *percentRow = R"(<tr><td width="200">Bottle Level</td><td>%d percent</td></tr>)";
    const char *adcRow = R"(<tr><td width="200">Raw Sensor Value</td><td>%ld</td></tr>)";
    const char *tableClosing = R"(</table>)";
    pos += snprintf(pos, end - pos, formOpening, _postUri);
    pos += snprintf(pos, end - pos, empty, CONST_EMPTY, _bottle.getEmpty());
    pos += snprintf(pos, end - pos, full, CONST_FULL, _bottle.getFull());
    pos += snprintf(pos, end - pos, formClosing);
    pos += snprintf(pos, end - pos, tableOpening);
    pos += snprintf(pos, end - pos, percentRow, _bottle.getPercent());
    pos += snprintf(pos, end - pos, adcRow, _bottle.getRaw());
    pos += snprintf(pos, end - pos, tableClosing);
    return pos - out;
}
