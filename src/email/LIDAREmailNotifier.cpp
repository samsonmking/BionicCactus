#include "LIDAREmailNotifier.hpp"

using namespace Time;
using namespace Sensors::Bottle;

namespace Email {

    LIDAREmailNotifier::LIDAREmailNotifier(MillisProvider& millisProvider, LidarBottle& bottle, EmailConfig& config) :
    _millisProvider(millisProvider),
    _timer(Timer(millisProvider, 2, Units::HOURS)), 
    _bottle(bottle),
    _config(config), 
    _warnLevel{25} {

    }

    void LIDAREmailNotifier::loop() {
        if(!_config.configured) return;
        if(_bottle.getPercent() > _warnLevel) return;
        if(!_timer.isExpired()) return;
        if(sendNotification()) {
            _timer.reset();
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