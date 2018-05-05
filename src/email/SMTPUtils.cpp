#include "SMTPUtils.hpp"

namespace Email {

    int getStatusCodeFromReply(uint8_t* buffer) {
        if (strlen((char *)buffer) < 3) {
            return -1;
        }
        char numChar[4] = {0,0,0,0};
        strncpy(numChar, (const char *)buffer, 3);
        for(int i = 0; i < 3; i++) {
            if (!isdigit(numChar[i])) {
                return -1;
            }
        }
        return atoi(numChar);
    }

}