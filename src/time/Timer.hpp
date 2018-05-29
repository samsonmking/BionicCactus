#ifndef TIMER_H
#define TIMER_H

#include "Timer.hpp"
#include "MillisProvider.hpp"
#include "TimeUnitConverter.hpp"

namespace Time {

    class Timer {
        public:
            Timer(MillisProvider& provider, unsigned long input, Units units);
            Timer(MillisProvider& provider, unsigned long input, Units units, bool fireAtStart);
            bool isExpired();
            void reset();
            void reset(unsigned long input, Units units, bool fireAtStart);
            void reset(unsigned long input, Units units);
        private:
            MillisProvider& _provider;
            unsigned long _interval;
            unsigned long _last;
            bool _fireAtStart;
    };

}

#endif