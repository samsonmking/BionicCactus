#include "EmailClient.hpp"

using namespace Time;

namespace Email {

    EmailClient::EmailClient(MillisProvider& millisProvider, const char* server, int port, const char* username, const char* password) :
    _timer(millisProvider, 5, Units::SECONDS), 
    _server(server), 
    _port(port), 
    _username(username), 
    _password(password) {

    }

    bool EmailClient::send(Message message) {
        WiFiClient client;
        client.connect(_server, _port);
        if(assertReplyNotCode(client, 220)) return false;
        client.println("EHLO bioniccactusclient");
        if(assertReplyNotCode(client, 250)) return false;
        client.println("AUTH LOGIN");
        if(assertReplyNotCode(client, 334)) return false;
        client.println(_username);
        if(assertReplyNotCode(client, 334)) return false;
        client.println(_password);
        if(assertReplyNotCode(client, 235)) return false;
        client.print("MAIL FROM: <");
        client.print(message.from);
        client.println(">");
        if(assertReplyNotCode(client, 250)) return false;
        client.print("RCPT TO: <");
        client.print(message.to);
        client.println(">");
        if(assertReplyNotCode(client, 250)) return false;
        client.println("DATA");
        if(assertReplyNotCode(client, 354)) return false;
        client.println("MIME-Version: 1.0");
        client.print("From: <");
        client.print(message.from);
        client.println(">");
        client.print("To: <");
        client.print(message.to);
        client.println(">");
        client.print("Subject: ");
        client.println(message.subject);
        client.println("Content-type: text/plain; charset=us-ascii");
        client.println("");
        client.println(message.body);
        client.println(".");
        if(assertReplyNotCode(client, 250)) return false;
        client.println("QUIT");
        if(assertReplyNotCode(client, 221)) return false;
        return true;
    }

    int EmailClient::getReplyCode(WiFiClient& client) {
        _timer.reset();
        while(client.available() == 0) {
            if (_timer.isExpired()) {
                return -1;
            }
        }

        static const int len = 200;
        uint8_t buffer[len];
        
        client.read(buffer, len);
        int code = getStatusCodeFromReply(buffer);

        while(client.available() > 0) {
            int r = client.read(buffer, len);
        }

        return code;
    }

    bool EmailClient::assertReplyNotCode(WiFiClient &client, int code) {
        return getReplyCode(client) != code;
    }

}