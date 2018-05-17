#include "EmailFileHandler.hpp"

using namespace Persistance;
using namespace Email;

EmailFileHandler::EmailFileHandler() : _config {"username", "password", "someserver.com", "you@domain.com", "notify@bioniccactus.io", 2, 587} {

}

void EmailFileHandler::load() {
    auto file = SPIFFS.open(_filePath, "r");
    if (!file) {
        _config.configured = false;
        return;
    }
    StaticJsonBuffer<CONST_FILE_LENGTH> jsonBuffer;
    auto &emailRoot = jsonBuffer.parseObject(file);
    file.close();
    strncpy(_config.username, emailRoot[CONST_USERNAME], sizeof(_config.username));
    strncpy(_config.password, emailRoot[CONST_PASSWORD], sizeof(_config.password));
    strncpy(_config.server, emailRoot[CONST_SERVER], sizeof(_config.server));
    strncpy(_config.to, emailRoot[CONST_TO], sizeof(_config.to));
    strncpy(_config.from, emailRoot[CONST_FROM], sizeof(_config.from));
    _config.port = emailRoot[CONST_PORT];
    _config.interval = emailRoot[CONST_INTERVAL];
    _config.configured = true;
}

void EmailFileHandler::save() {
    StaticJsonBuffer<CONST_FILE_LENGTH> jsonBuffer;
    auto &emailRoot = jsonBuffer.createObject();
    emailRoot[CONST_USERNAME] = _config.username;
    emailRoot[CONST_PASSWORD] = _config.password;
    emailRoot[CONST_SERVER] = _config.server;
    emailRoot[CONST_TO] = _config.to;
    emailRoot[CONST_FROM] = _config.from;
    emailRoot[CONST_PORT] = _config.port;
    emailRoot[CONST_INTERVAL] = _config.interval;
    auto file = SPIFFS.open(_filePath, "w");
    emailRoot.printTo(file);
    file.close();
    _config.configured = true;
}

EmailConfig& EmailFileHandler::getConfig() {
    return _config;
}