#ifndef NTP_H
#define NTP_H

#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TimeProvider.hpp>

class NTP: public TimeProvider {
public:
  static NTP* getInstance();
  virtual time_t getCurrentTime();
  time_t getNTPTime();
private:
  NTP();
  void begin();
  static NTP* s_ntp;
  static time_t s_getNTPTime();
  const char* _ntpServerName = "us.pool.ntp.org";
  unsigned int _port = 8888;
  const int NTP_PACKET_SIZE = 48;
  byte packetBuffer[48];
  WiFiUDP _udp;
  void sendNTPpacket(IPAddress &address);
  bool _started = false;
};

#endif
