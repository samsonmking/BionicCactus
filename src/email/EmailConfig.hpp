#ifndef EMAIL_CONFIG_H
#define EMAIL_CONFIG_H

namespace Email {

    typedef struct {
        char username[50];
        char password[100];
        char server[50];
        char to[50];
        char from[50];
        int interval;
        int port;
        bool configured;
    } EmailConfig;

}

#endif
