#include "EmailPostRequestHandler.hpp"

using namespace Web;
using namespace Email;
using namespace Persistance;

EmailPostRequestHandler::EmailPostRequestHandler(const char* uri, EmailFileHandler& configFile) :
_uri(uri), _configFile(configFile) {

}

void EmailPostRequestHandler::setVals(PostParameter postParams[], int numParams) {
    Email::EmailConfig& config = _configFile.getConfig();
    for(int i = 0; i < numParams; i++) {
        if(strcmp(postParams[i].key, CONST_USERNAME) == 0) {
            strncpy(config.username, postParams[i].value, sizeof(config.username));
            continue;
        }
        if(strcmp(postParams[i].key, CONST_PASSWORD) == 0) {
            strncpy(config.password, postParams[i].value, sizeof(config.password));
            continue;
        }
        if(strcmp(postParams[i].key, CONST_SERVER) == 0) {
            strncpy(config.server, postParams[i].value, sizeof(config.server));
            continue;
        }
        if(strcmp(postParams[i].key, CONST_PORT) == 0) {
            config.port = atoi(postParams[i].value);
            continue;
        }
        if(strcmp(postParams[i].key, CONST_TO) == 0) {
            strncpy(config.to, postParams[i].value, sizeof(config.to));
            continue;
        }
        if(strcmp(postParams[i].key, CONST_FROM) == 0) {
            strncpy(config.from, postParams[i].value, sizeof(config.from));
            continue;
        }
        if(strcmp(postParams[i].key, CONST_INTERVAL) == 0) {
            config.interval = atoi(postParams[i].value);
            continue;
        }
    }
    _configFile.save();
}

const char* EmailPostRequestHandler::getURI() {
    return _uri;
}