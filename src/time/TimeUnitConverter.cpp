#include "TimeUnitConverter.hpp"

namespace Time {

    unsigned long convertMillis(unsigned long input, Units units) {

        switch(units) {
            case Units::MILLISECONDS:
                return input;
            case Units::SECONDS:
                return input * 1000;
            case Units::MINUTES:
                return input * 60000;
            case Units::HOURS:
                return input * 3600000;
            case Units::DAYS:
                return input * 86400000;
            default:
                return 0;
        }

    }

}