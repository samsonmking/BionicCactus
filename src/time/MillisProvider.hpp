#ifndef MILLIS_PROVIDER_H
#define MILLIS_PROVIDER_H

namespace Time {

    class MillisProvider {
        public:
            virtual unsigned long getMillis() = 0;
    };

}

#endif