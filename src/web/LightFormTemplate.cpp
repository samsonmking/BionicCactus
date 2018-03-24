#include <web/LightFormTemplate.hpp>

LightFormTemplate::LightFormTemplate(const char *postUri, Light *light) : _postUri(postUri), _light(light) {
    
}

void LightFormTemplate::getForm(char *out) {
    char *pos = out + strlen(out);
    const char *formOpening = R"(<Form action="/config/submit" method="post">)";
    const char *brightnessInput = R"(Brightness<br><input type = "text" name = "brightness" value = "%d"><br>)";
    const char *timeOnInput = R"(Time On<br><input type = "text" name = "timeOn" value = "%s"><br>)";
    const char *timeOffInput = R"(Time Off<br><input type = "text" name = "timeOff" value = "%s"><br>)";
    const char *formClosing = R"(<input type="submit" value="Submit"></Form>)";
    pos += sprintf(pos, formOpening);
    pos += sprintf(pos, brightnessInput, _light->getBrightness());
    pos += sprintf(pos, timeOnInput, _light->getTimeOn());
    pos += sprintf(pos, timeOffInput, _light->getTimeOff());
    pos += sprintf(pos, formClosing);
}