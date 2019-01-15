#ifndef MOCK_BOTTLE_H
#define MOCK_BOTTLE_H

namespace Sensors {
    namespace Bottle {

        class MockBottle : public Bottle {
            public:
                void init() override {
                    // Dummy init
                }
                int getPercent() override {
                    return 75;
                };

                long getRaw() override {
                    return 1000;
                }
                long getEmpty() override {
                    return _empty;
                }
                void setEmpty(long empty) override {
                    _empty = empty;
                }
                long getFull() override {
                    return _full;
                }
                void setFull(long full) override {
                    _full = full;
                }
            private:
                long _empty = 50;
                long _full = 5000;
        };
    }
}

#endif
