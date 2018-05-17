#include "web/email/EmailFormTemplate.hpp"

using namespace Web;
using namespace Email;

EmailFormTemplate::EmailFormTemplate(const char* postUri, EmailConfig& config) :
_postUri(postUri), _config(config) {

} 

int EmailFormTemplate::getForm(char* out, size_t len) {
    char* pos = out;
    char* end = out + len;

    const char *formOpening = R"(<Form action="%s" method="post">)";
    const char *username = R"(<p>Username<br><input type = "text" name = "%s" value = "%s"> Base64</p>)";
    const char *password = R"(<p>Password<br><input type = "text" name = "%s" value = "%s"> Base64</p>)";
    const char *server = R"(<p>Server<br><input type = "text" name = "%s" value = "%s"></p>)";
    const char *port = R"(<p>Port<br><input type = "text" name = "%s" value = "%d"></p>)";
    const char *to = R"(<p>To<br><input type = "text" name = "%s" value = "%s"></p>)";
    const char *from = R"(<p>From<br><input type = "text" name = "%s" value = "%s"></p>)";
    const char *interval = R"(<p>Interval<br><input type = "text" name = "%s" value = "%d"> hrs</p>)";
    const char *formClosing = R"(<input type="submit" value="Submit"></Form>)";

    pos += snprintf(pos, end - pos, formOpening, _postUri);
    pos += snprintf(pos, end - pos, username, CONST_USERNAME, _config.username);
    pos += snprintf(pos, end - pos, password, CONST_PASSWORD, _config.password);
    pos += snprintf(pos, end - pos, server, CONST_SERVER, _config.server);
    pos += snprintf(pos, end - pos, port, CONST_PORT, _config.port);
    pos += snprintf(pos, end - pos, to, CONST_TO, _config.to);
    pos += snprintf(pos, end - pos, from, CONST_FROM, _config.from);
    pos += snprintf(pos, end - pos, interval, CONST_INTERVAL, _config.interval);
    pos += snprintf(pos, end - pos, formClosing);

    return pos - out;
}