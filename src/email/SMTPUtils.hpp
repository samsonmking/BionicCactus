#ifndef SMTPUTILS_H
#define SMTPUTILS_H

#include <Arduino.h>

namespace Email {

    // Returns 3 digit SMTP status code or -1 if unable to parse code
    int getStatusCodeFromReply(uint8_t* buffer);

}

#endif