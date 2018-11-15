#ifndef SCALE_BOTTLE_H
#define SCALE_BOTTLE_H

#include "Bottle.hpp"
#include "HX711.h"

namespace Sensors {
    namespace Bottle {

        class ScaleBottle : public Bottle {
            public:
                ScaleBottle(int dout, int sck);
                long getRaw() override;
                int getPercent() override;
                long getEmpty() override;
                void setEmpty(long empty) override;
                long getFull() override;
                void setFull(long full) override;
            private:
                HX711 _scale;
                long _empty;
                long _full;
                double _m;
                double _b;
                void calculateConstants();
        };

    }
}

#endif
