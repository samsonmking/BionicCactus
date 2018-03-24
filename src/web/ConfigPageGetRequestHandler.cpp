#include <web/ConfigPageGetRequestHandler.hpp>

ConfigPageGetRequestHandler::ConfigPageGetRequestHandler(const char *uri, const char *title, const char *h1, SettingsFormTemplate *formTemplate) : 
_uri(uri), 
_title(title), 
_h1(h1),
_formTemplate(formTemplate) {

}

void ConfigPageGetRequestHandler::getHTML(char *out) {
    formatHeader(out);
    formatForm(out);
    formatFooter(out);
}

void ConfigPageGetRequestHandler::formatHeader(char *out) {
    const char *pageHeader = R"(
    <html>
        <head>
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>%s</title>
        </head>
        <h1>%s</h1>)";
    sprintf(out + strlen(out), pageHeader, _title, _h1);
}

void ConfigPageGetRequestHandler::formatForm(char *out) {
    _formTemplate->getForm(out + strlen(out));
}

void ConfigPageGetRequestHandler::formatFooter(char *out) {
    const char *pageFooter = R"(
    </html>
    )";
    sprintf(out + strlen(out), pageFooter);
}