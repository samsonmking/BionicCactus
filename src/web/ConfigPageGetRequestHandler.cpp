#include <web/ConfigPageGetRequestHandler.hpp>

ConfigPageGetRequestHandler::ConfigPageGetRequestHandler(const char *uri, const char *title, const char *h1, SettingsFormTemplate *formTemplate) : 
_uri(uri), 
_title(title), 
_h1(h1),
_formTemplate(formTemplate) {

}

void ConfigPageGetRequestHandler::getHTML(char *out, size_t len) {
    char *pos = out;
    char *end = out + len;
    pos += formatHeader(pos, end - pos);
    pos += formatForm(pos, end - pos);
    pos += formatFooter(pos, end - pos);
}

int ConfigPageGetRequestHandler::formatHeader(char *out, size_t len) {
    const char *pageHeader = R"(
    <html>
        <head>
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>%s</title>
        </head>
        <h1>%s</h1>)";
    return snprintf(out, len, pageHeader, _title, _h1);
}

int ConfigPageGetRequestHandler::formatForm(char *out, size_t len) {
    return _formTemplate->getForm(out, len);
}

int ConfigPageGetRequestHandler::formatFooter(char *out, size_t len) {
    const char *pageFooter = R"(
    </html>
    )";
    return snprintf(out, len, pageFooter);
}