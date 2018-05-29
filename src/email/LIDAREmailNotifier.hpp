#ifndef LIDAR_EMAIL_H
#define LIDAR_EMAIL_H

#include "time/MillisProvider.hpp"
#include "time/Timer.hpp"
#include "sensors/bottle/LIDARBottle.hpp"
#include "email/EmailClient.hpp"
#include "email/EmailConfig.hpp"

namespace Email {

    class LIDAREmailNotifier {
        public:
            LIDAREmailNotifier(Time::MillisProvider& millisProvider, 
                Sensors::Bottle::LidarBottle& bottle,
                EmailConfig& config);
            void loop();
        private:
            Time::MillisProvider& _millisProvider;
            Time::Timer _timer;
            Sensors::Bottle::LidarBottle& _bottle;
            EmailConfig& _config;
            int _warnLevel;
            char _bodyBuffer[100];
            bool sendNotification();           
            const char* formatBody();
    };

}

#endif