#ifndef SCALE_BOTTLE_H
#define SCALE_BOTTLE_H

#include "Bottle.hpp"
#include "HX711.h"

namespace Sensors {
    namespace Bottle {

        class ScaleBottle : public Bottle {
            public:
                ScaleBottle(int dout, int sck);
                long getRaw();
                virtual int getPercent() override;
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
