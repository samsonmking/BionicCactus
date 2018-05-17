#include "LIDAREmailNotifier.hpp"

using namespace Time;
using namespace Sensors::Bottle;

namespace Email {

    LIDAREmailNotifier::LIDAREmailNotifier(Clock& clock, LidarBottle& bottle, EmailConfig& config) :
    _clock(clock), 
    _bottle(bottle),
    _config(config), 
    _warnLevel{25}, 
    _interval{7200000},
    _lastNotified{0} {

    }

    void LIDAREmailNotifier::loop() {
        if(!_config.configured) return;
        if(_bottle.getPercent() > _warnLevel) return;
        if((_clock.getMillis() - _lastNotified) < 5000) return;
        if(sendNotification()) {
            _lastNotified = _clock.getMillis();
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
        EmailClient client(_clock, 
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