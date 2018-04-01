#ifndef HEADER_H
#define HEADER_H

#include <Arduino.h>

class Header {
public:
    int getHeader(char *out, size_t len);
};

#endif