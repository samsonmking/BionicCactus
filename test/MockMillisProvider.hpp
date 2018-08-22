#ifndef MOCK_MILLIS_H
#define MOCK_MILLIS_H

#include "time/MillisProvider.hpp"

namespace Time {

    class MockMillisProvider : public MillisProvider {
        public:
            MockMillisProvider(unsigned long m) : _m(m) {

            }
            unsigned long getMillis() override {
                return _m;
            }
            void setMillis(unsigned long m) {
                _m = m;
            }
        private:
            unsigned long _m;
    };

}

#endif