#ifndef VALUES_DASH_TEMPLATE_H
#define VALUES_DASH_TEMPLATE_H

#include <Arduino.h>

class ValuesDashboardTemplate {
public:
    virtual int getDashboard(char *out, size_t len) = 0;
};

#endif