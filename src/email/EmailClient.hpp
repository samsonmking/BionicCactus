#ifndef EMAIL_CLIENT_H
#define EMAIL_CLIENT_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "time/Clock.hpp"
#include "SMTPUtils.hpp"

namespace Email {

    typedef struct {
        const char* to;
        const char* from;
        const char* subject;
        const char* body;
    } Message;

    class EmailClient {
        public:
            EmailClient(Time::Clock& clock, const char* server, int port, const char* username, const char* password);
            bool send(Message message);
        private:
            Time::Clock& _clock;
            const char* _server;
            int _port;
            const char* _username;
            const char* _password;
            void send(const char* payload);
            int getReplyCode(WiFiClient& client);
            bool assertReplyNotCode(WiFiClient& client, int code);
    };

}

#endif