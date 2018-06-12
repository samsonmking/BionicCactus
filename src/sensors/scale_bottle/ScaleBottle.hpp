#ifndef SCALE_BOTTLE_H
#define SCALE_BOTTLE_H

#include "HX711.h"

namespace Sensors {
    namespace Bottle {

        class ScaleBottle {
            public:
                ScaleBottle(int dout, int sck);
                long getRaw();
                int getPercent();
            private:
                HX711 _scale;
                long _low;
                long _high;
                double _m;
                double _b;
                void calculateConstants();
        };

    }
}

#endif