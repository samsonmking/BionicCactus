#include "LIDAREmailNotifier.hpp"

using namespace Time;
using namespace Sensors::Bottle;

namespace Email {

    LIDAREmailNotifier::LIDAREmailNotifier(MillisProvider& millisProvider, LidarBottle& bottle, EmailConfig& config) :
    _millisProvider(millisProvider),
    _timer(Timer(millisProvider, 2, Units::HOURS)), 
    _bottle(bottle),
    _config(config),
    _state(NotificationStates::CHECKING), 
    _warnLevel{25} {

    }

    void LIDAREmailNotifier::loop() {
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
    }

    void LIDAREmailNotifier::enterChecking() {
        _state = NotificationStates::CHECKING;
    }

    void LIDAREmailNotifier::checking() {
        if (_bottle.getPercent() < _warnLevel) {
             enterPending();
        }
    }

    void LIDAREmailNotifier::enterPending() {
        _timer.reset(10, Units::MINUTES);
        _state = NotificationStates::PENDING;
    }

    void LIDAREmailNotifier::pending() {
        if(_bottle.getPercent() > _warnLevel) {
            enterChecking();
            return;
        }
        if(_timer.isExpired()) {
            enterSending();
        }
    }

    void LIDAREmailNotifier::enterSending() {
        _state = NotificationStates::SENDING;
    }

    void LIDAREmailNotifier::sending() {
        if (sendNotification()) {
            enterWaiting();
        } else {
            enterPending();
        }
    }

    void LIDAREmailNotifier::enterWaiting() {
        _timer.reset(2, Units::HOURS);
        _state = NotificationStates::WAITING;
    }

    void LIDAREmailNotifier::waiting() {
        if(_timer.isExpired()) {
            enterChecking();
        }
    }

    bool LIDAREmailNotifier::sendNotification() {
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

    const char* LIDAREmailNotifier::formatBody() {
        snprintf(_bodyBuffer, sizeof(_bodyBuffer), "Water level currently at %d, which is below warn level of %d, please fill me!", _bottle.getPercent(), _warnLevel);
        return _bodyBuffer;
    }
}