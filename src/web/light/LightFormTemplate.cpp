#include <web/light/LightFormTemplate.hpp>

LightFormTemplate::LightFormTemplate(const char *postUri, Light *light) : _postUri(postUri), _light(light) {
    
}

int LightFormTemplate::getForm(char *out, size_t len) {
    char *pos = out;
    char *end = out + len;
    const char *formOpening = R"(<Form action="%s" method="post">)";
    const char *brightnessInput = R"(Brightness<br><input type = "text" name = "brightness" value = "%d"><br>)";
    const char *timeOnInput = R"(Time On<br><input type = "text" name = "timeOn" value = "%s"><br>)";
    const char *timeOffInput = R"(Time Off<br><input type = "text" name = "timeOff" value = "%s"><br>)";
    const char *formClosing = R"(<input type="submit" value="Submit"></Form>)";
    
    pos += snprintf(pos, end - pos, formOpening, _postUri);
    pos += snprintf(pos, end - pos, brightnessInput, _light->getBrightness());
    pos += snprintf(pos, end - pos, timeOnInput, _light->getTimeOn());
    pos += snprintf(pos, end - pos, timeOffInput, _light->getTimeOff());
    pos += snprintf(pos, end - pos, formClosing);
    return pos - out;
}