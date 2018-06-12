#ifndef BOTTLE_EMAIL_H
#define BOTTLE_EMAIL_H

#include "time/MillisProvider.hpp"
#include "time/Timer.hpp"
#include "sensors/scale_bottle/ScaleBottle.hpp"
#include "email/EmailClient.hpp"
#include "email/EmailConfig.hpp"

namespace Email {

    enum class NotificationStates {
        CHECKING,
        PENDING,
        SENDING,
        WAITING
    };

    class BottleEmailNotifier {
        public:
            BottleEmailNotifier(Time::MillisProvider& millisProvider, 
                Sensors::Bottle::ScaleBottle& bottle,
                EmailConfig& config);
            void loop();
        private:
            Time::MillisProvider& _millisProvider;
            Time::Timer _timer;
            Time::Timer _interval;
            Sensors::Bottle::ScaleBottle& _bottle;
            EmailConfig& _config;
            NotificationStates _state;
            int _warnLevel;
            char _bodyBuffer[100];
            bool sendNotification();           
            const char* formatBody();
            void enterChecking();
            void checking();
            void enterPending();
            void pending();
            void enterSending();
            void sending();
            void enterWaiting();
            void waiting();
    };

}

#endif