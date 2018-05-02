#include "NTPTimeProvider.hpp"

namespace Time {

    NTPTimeProvider::NTPTimeProvider(UDP& udp) :
        _udp(udp),
        _udpSetup(false),
        _port(1337),
        _updateInterval(60000),
        _lastUpdate(0),
        _currentEpoc(0) {

    }

    unsigned long NTPTimeProvider::getMillis() {
        return millis();
    }

    time_t NTPTimeProvider::getCurrentTime() {
        return _currentEpoc + ((millis() - this->_lastUpdate) / 1000);
    }

    bool NTPTimeProvider::update() {
        if ((millis() - _lastUpdate >= _updateInterval) || this->_lastUpdate == 0) {
            if (!_udpSetup) begin();
            return forceUpdate();
        }
        return true;
    }

    bool NTPTimeProvider::forceUpdate() {
        sendNTPPacket();

        // Wait till data is there or timeout...
        byte timeout = 0;
        int cb = 0;
        do {
            delay ( 10 );
            cb = _udp.parsePacket();
            if (timeout > 100) return false; // timeout after 1000 ms
            timeout++;
        } while (cb == 0);

        _lastUpdate = millis() - (10 * (timeout + 1)); // Account for delay in reading the time

        _udp.read(_packetBuffer, NTP_PACKET_SIZE);

        unsigned long highWord = word(_packetBuffer[40], _packetBuffer[41]);
        unsigned long lowWord = word(_packetBuffer[42], _packetBuffer[43]);
        // combine the four bytes (two words) into a long integer
        // this is NTP time (seconds since Jan 1 1900):
        unsigned long secsSince1900 = highWord << 16 | lowWord;

        _currentEpoc = secsSince1900 - SEVENZYYEARS;

        return true;
    }

    void NTPTimeProvider::begin() {
        _udp.begin(_port);
        _udpSetup = true;
    }

    void NTPTimeProvider::end() {
        _udp.stop();
        _udpSetup = false;
    }

    void NTPTimeProvider::sendNTPPacket() {
        // set all bytes in the buffer to 0
        memset(_packetBuffer, 0, NTP_PACKET_SIZE);
        // Initialize values needed to form NTP request
        // (see URL above for details on the packets)
        _packetBuffer[0] = 0b11100011;   // LI, Version, Mode
        _packetBuffer[1] = 0;     // Stratum, or type of clock
        _packetBuffer[2] = 6;     // Polling Interval
        _packetBuffer[3] = 0xEC;  // Peer Clock Precision
        // 8 bytes of zero for Root Delay & Root Dispersion
        _packetBuffer[12]  = 49;
        _packetBuffer[13]  = 0x4E;
        _packetBuffer[14]  = 49;
        _packetBuffer[15]  = 52;

        // all NTP fields have been given values, now
        // you can send a packet requesting a timestamp:
        _udp.beginPacket(this->_poolServerName, 123); //NTP requests are to port 123
        _udp.write(this->_packetBuffer, NTP_PACKET_SIZE);
        _udp.endPacket();
    }

}
