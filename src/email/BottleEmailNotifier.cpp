#include "BottleEmailNotifier.hpp"

using namespace Time;
using namespace Sensors::Bottle;

namespace Email {

    BottleEmailNotifier::BottleEmailNotifier(MillisProvider& millisProvider, Bottle& bottle, EmailConfig& config) :
    _millisProvider(millisProvider),
    _timer(Timer(millisProvider, 2, Units::HOURS)),
    _interval(Timer(millisProvider, 10, Units::SECONDS)), 
    _bottle(bottle),
    _config(config),
    _state(NotificationStates::CHECKING), 
    _warnLevel{25} {

    }

    void BottleEmailNotifier::loop() {
        if(_interval.isExpired() == false) {
            return;
        }

        switch(_state) {
            case NotificationStates::CHECKING:
                checking();
                break;
            case NotificationStates::PENDING:
                pending();
                break;
            case NotificationStates::SENDING:
                sending();
                break;
            case NotificationStates::WAITING:
                waiting();
                break;
        }
        
        _interval.reset();
    }

    void BottleEmailNotifier::enterChecking() {
        _state = NotificationStates::CHECKING;
    }

    void BottleEmailNotifier::checking() {
        if (_bottle.getPercent() < _warnLevel) {
             enterPending();
        }
    }

    void BottleEmailNotifier::enterPending() {
        _timer.reset(10, Units::MINUTES);
        _state = NotificationStates::PENDING;
    }

    void BottleEmailNotifier::pending() {
        if(_bottle.getPercent() > _warnLevel) {
            enterChecking();
            return;
        }
        if(_timer.isExpired()) {
            enterSending();
        }
    }

    void BottleEmailNotifier::enterSending() {
        _state = NotificationStates::SENDING;
    }

    void BottleEmailNotifier::sending() {
        if (sendNotification()) {
            enterWaiting();
        } else {
            enterPending();
        }
    }

    void BottleEmailNotifier::enterWaiting() {
        _timer.reset(2, Units::HOURS);
        _state = NotificationStates::WAITING;
    }

    void BottleEmailNotifier::waiting() {
        if(_timer.isExpired()) {
            enterChecking();
        }
    }

    bool BottleEmailNotifier::sendNotification() {
        Serial.println("sending email");
        Message message {
            _config.to,
            _config.from,
            "Water Level Warning",
            formatBody()
        };
        EmailClient client(_millisProvider, 
            _config.server, 
            _config.port, 
            _config.username, 
            _config.password);
        return client.send(message);
    }

    const char* BottleEmailNotifier::formatBody() {
        snprintf(_bodyBuffer, sizeof(_bodyBuffer), "Water level currently at %d, which is below warn level of %d, please fill me!", _bottle.getPercent(), _warnLevel);
        return _bodyBuffer;
    }
}
