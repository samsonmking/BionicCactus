#ifndef CLOCK_H
#define CLOCK_H

#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

class Clock {
public:
  static Clock* getInstance();
  void begin();
  bool isATOrPastTime(const char* timeChr);
  time_t getTimeFromChr(char* input);
  time_t getNTPTime();
  void getTimeChr(char* out, time_t moment);
  void getTimeNowChr(char* out);
  unsigned int getSecondsSinceMidnight(time_t time);
  unsigned int getSecondsSinceMidnight(const char* timeChr);


private:
  Clock();
  static Clock* s_clock;
  static time_t s_getNTPTime();
  const char* _ntpServerName = "us.pool.ntp.org";
  unsigned int _port = 8888;
  int _timeZone = -4;
  const int NTP_PACKET_SIZE = 48;
  byte packetBuffer[48];
  WiFiUDP _udp;
  void sendNTPpacket(IPAddress &address);
  void printDigits(char* out, int digits);
};

#endif
