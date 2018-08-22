#ifndef NTP_PROVIDER_H
#define NTP_PROVIDER_H

#include "TimeProvider.hpp"
#include <Arduino.h>
#include <Udp.h>

namespace Time {

    #define NTP_PACKET_SIZE 48
    #define SEVENZYYEARS 2208988800UL

    class NTPTimeProvider : public TimeProvider {
        public:
            NTPTimeProvider(UDP& udp);
            virtual unix_time_t getCurrentTime() override;
            bool update();
            bool forceUpdate();
        private:
            UDP& _udp;
            bool _udpSetup;
            const char* _poolServerName = "time.nist.gov";
            int _port;
            unsigned long _lastUpdate;
            unsigned int _updateInterval;
            unsigned long _currentEpoc;

            byte _packetBuffer[NTP_PACKET_SIZE];
            void begin();
            void end();
            void sendNTPPacket();

    };

}

#endif