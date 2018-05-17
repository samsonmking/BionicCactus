#ifndef LIDAR_EMAIL_H
#define LIDAR_EMAIL_H

#include "time/Clock.hpp"
#include "sensors/bottle/LIDARBottle.hpp"
#include "email/EmailClient.hpp"
#include "email/EmailConfig.hpp"

namespace Email {

    class LIDAREmailNotifier {
        public:
            LIDAREmailNotifier(Time::Clock& clock, 
                Sensors::Bottle::LidarBottle& bottle,
                EmailConfig& config);
            void loop();
        private:
            Time::Clock& _clock;
            Sensors::Bottle::LidarBottle& _bottle;
            EmailConfig& _config;
            int _warnLevel;
            int _interval;
            unsigned long _lastNotified;
            char _bodyBuffer[100];
            bool sendNotification();           
            const char* formatBody();
    };

}

#endif