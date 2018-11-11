#ifndef MOCK_BOTTLE_H
#define MOCK_BOTTLE_H

namespace Sensors {
    namespace Bottle {

        class MockBottle : public Bottle {
            public:
                virtual int getPercent() {
                    return 75;
                };

        };
    }
}

#endif
