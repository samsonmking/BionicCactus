#ifndef TIME_UNIT_CONVERTER_H
#define TIME_UNIT_CONVERTER_H

namespace Time {

    enum class Units {
        MILLISECONDS,
        SECONDS,
        MINUTES,
        HOURS,
        DAYS
    };

    unsigned long convertMillis(unsigned long input, Units units);

}

#endif