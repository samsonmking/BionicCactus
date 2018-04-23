#include "NTP.hpp"

using namespace Time;

NTP::NTP() {
}

NTP* NTP::s_ntp = 0;

NTP* NTP::getInstance() {
  if (!s_ntp) {
    s_ntp = new NTP();
  }
  return s_ntp;
}

time_t NTP::getCurrentTime() {
  if (!_started) {
    s_ntp->begin();
    _started = true;
  }
  return now();
}

unsigned long NTP::getMillis() {
  return millis();
}

void NTP::begin() {
  _udp.begin(_port);
  setSyncProvider(s_getNTPTime);
  setSyncInterval(300);
}

time_t NTP::s_getNTPTime() {
  return s_ntp->getNTPTime();
}

time_t NTP::getNTPTime() {
  IPAddress ntpServerIP; // NTP server's ip address
    while (_udp.parsePacket() > 0) ; // discard any previously received packets
    // get a random server from the pool
    WiFi.hostByName(_ntpServerName, ntpServerIP);
    sendNTPpacket(ntpServerIP);
    uint32_t beginWait = millis();
    while (millis() - beginWait < 1500) {
      int size = _udp.parsePacket();
      if (size >= NTP_PACKET_SIZE) {
        _udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
        unsigned long secsSince1900;
        // convert four bytes starting at location 40 to a long integer
        secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
        secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
        secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
        secsSince1900 |= (unsigned long)packetBuffer[43];
        return secsSince1900 - 2208988800UL;
      }
    }
    Serial.println("No NTP Response :-(");
    return 0; // return 0 if unable to get the time
}

void NTP::sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  _udp.beginPacket(address, 123); //NTP requests are to port 123
  _udp.write(packetBuffer, NTP_PACKET_SIZE);
  _udp.endPacket();
}
