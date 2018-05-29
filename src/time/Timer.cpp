#include "Timer.hpp"

namespace Time {

    Timer::Timer(MillisProvider& provider, unsigned long input, Units units) :
    _provider(provider),
    _interval{convertMillis(input, units)},
    _last{provider.getMillis()},
    _fireAtStart{false} {

    }

    Timer::Timer(MillisProvider& provider, unsigned long input, Units units, bool fireAtStart = false) :
    _provider(provider),
    _interval{convertMillis(input, units)},
    _last{provider.getMillis()},
    _fireAtStart{fireAtStart} {

    }

    bool Timer::isExpired() {
        return _fireAtStart || ((_provider.getMillis() - _last) >= _interval);  
    }

    void Timer::reset() {
        _fireAtStart = false;
        _last = _provider.getMillis();
    }

    void Timer::reset(unsigned long input, Units units, bool fireAtStart) {
        _interval = convertMillis(input, units);
        _fireAtStart = fireAtStart;
        _last = _provider.getMillis();
    }

    void Timer::reset(unsigned long input, Units units) {
        reset(input, units, false);
    }

}