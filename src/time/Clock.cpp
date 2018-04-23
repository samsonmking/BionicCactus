#include "Clock.hpp"

using namespace Time;

Clock::Clock(TimeProvider* timeProvider, int timeZone): _timeProvider(timeProvider), timeZone(timeZone) {

}

time_t Clock::getCurrentTime() {
  return _timeProvider->getCurrentTime()  + (timeZone * SECS_PER_HOUR);
}

void Clock::getTimeNowChr(char* out) {
  return getTimeChr(out, getCurrentTime());
}

bool Clock::isAtOrPastTime(const char* timeChr)
{
  time_t timeNow = getCurrentTime();
  int secsNow = getSecondsSinceMidnight(timeNow);
  int secsDesired = getSecondsSinceMidnight(timeChr);
  return secsNow >= secsDesired;
}

unsigned int Clock::getSecondsSinceMidnight(time_t moment) {
  return (hour(moment) * 3600) + (minute(moment) * 60) + (second(moment));
}

unsigned int Clock::getSecondsSinceMidnight(const char* timeChr)
{
  char test[9];
  strcpy(test, timeChr);
  char * pt;
  pt = strtok(test, ":");
  int hours = atoi(pt);
  pt = strtok(NULL, ":");
  int minutes = atoi(pt);
  pt = strtok(NULL, ":");
  int seconds = atoi(pt);
  return (hours * 3600) + (minutes * 60) + seconds;
}

void Clock::getTimeChr(char* out, time_t moment) {
  char hr[3] = "00";
  printDigits(hr, hour(moment));
  char min[3] = "00";
  printDigits(min, minute(moment));
  char sec[3] = "00";
  printDigits(sec, second(moment));
  snprintf(out, 9, "%s:%s:%s", hr, min, sec);
}

void Clock::printDigits(char* out, int digits) {
  if (digits < 10) {
    snprintf(out, 3, "%d%d", 0, digits);
  }
  else {
    snprintf(out, 3, "%d", digits);
  }
}
