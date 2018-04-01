#include <web/ConfigPageGetRequestHandler.hpp>

ConfigPageGetRequestHandler::ConfigPageGetRequestHandler(const char *uri, const char *subheading, Header &header, SettingsFormTemplate *formTemplate) : 
_uri(uri),
_subheading(subheading), 
_header(header),
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
    char *pos = out;
    char *end = out + len;
    pos += _header.getHeader(pos, end-pos);
    pos += snprintf(pos, end - pos, "<h2>%s</h2>", _subheading);
    return pos - out;
}

int ConfigPageGetRequestHandler::formatForm(char *out, size_t len) {
    return _formTemplate->getForm(out, len);
}

int ConfigPageGetRequestHandler::formatFooter(char *out, size_t len) {
    const char *pageFooter = R"(
    </body>
    </html>
    )";
    return snprintf(out, len, pageFooter);
}