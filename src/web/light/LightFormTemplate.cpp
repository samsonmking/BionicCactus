#include "web/light/LightFormTemplate.hpp"

using namespace Web;

LightFormTemplate::LightFormTemplate(const char *postUri, Light *light) : _postUri(postUri), _light(light) {
    
}

int LightFormTemplate::getForm(char *out, size_t len) {
    char *pos = out;
    char *end = out + len;
    const char *formOpening = R"(<Form action="%s" method="post">)";
    const char *enable = R"(<p>Enable<br><input type="checkbox" name="%s" value="true" %s></p>)";
    const char *brightnessInput = R"(<p>Brightness<br><input type = "text" name = "brightness" value = "%d"></p>)";
    const char *timeOnInput = R"(<p>Time On<br><input type = "text" name = "timeOn" value = "%s"></p>)";
    const char *timeOffInput = R"(<p>Time Off<br><input type = "text" name = "timeOff" value = "%s"></p>)";
    const char *formClosing = R"(<input type="submit" value="Submit"></Form>)";
    
    pos += snprintf(pos, end - pos, formOpening, _postUri);
    pos += snprintf(pos, end - pos, enable, CONST_LIGHT_ENABLE, _light->getEnabled() ? "checked" : "");
    pos += snprintf(pos, end - pos, brightnessInput, _light->getBrightness());
    pos += snprintf(pos, end - pos, timeOnInput, _light->getTimeOn());
    pos += snprintf(pos, end - pos, timeOffInput, _light->getTimeOff());
    pos += snprintf(pos, end - pos, formClosing);
    return pos - out;
}
