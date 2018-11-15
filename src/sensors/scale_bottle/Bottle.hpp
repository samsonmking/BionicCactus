#ifndef BOTTLE_H
#define BOTTLE_H

namespace Sensors {
    namespace Bottle {

        class Bottle {
            public:
                virtual long getRaw() = 0;;
                virtual int getPercent() = 0;
                virtual long getEmpty() = 0;
                virtual void setEmpty(long empty) = 0;
                virtual long getFull() = 0;
                virtual void setFull(long full) = 0;
        };

    }
}

#endif
