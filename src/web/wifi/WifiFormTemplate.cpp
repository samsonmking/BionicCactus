#include "web/wifi/WifiFormTemplate.hpp"

using namespace Web;

WifiFormTemplate::WifiFormTemplate(const char *postUri, WifiFileHandler &wifi) :
_postUri(postUri), _wifi(wifi) {

}

int WifiFormTemplate::getForm(char *out, size_t len) {
    char *pos = out;
    char *end = out + len;

    const char *formOpening = R"(<Form action="%s" method="post">)";
    const char *ssid = R"(<p>SSID<br><input type = "text" name = "%s" value = "%s"></p>)";
    const char *password = R"(<p>Password<br><input type = "text" name = "%s" value = "%s"></p>)";
    const char *hostname = R"(<p>Hostname<br><input type = "text" name = "%s" value = "%s"></p>)";
    const char *formClosing = R"(<input type="submit" value="Submit"></Form>)";

    pos += snprintf(pos, end - pos, formOpening, _postUri);
    pos += snprintf(pos, end - pos, ssid, CONST_SSID, _wifi.getSSID());
    pos += snprintf(pos, end - pos, password, CONST_PASSWORD, _wifi.getPassword());
    pos += snprintf(pos, end - pos, hostname, CONST_HOSTNAME, _wifi.getHostname());
    pos += snprintf(pos, end - pos, formClosing);

    return pos - out;
}
