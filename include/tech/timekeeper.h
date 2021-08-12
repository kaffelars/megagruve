#ifndef TIMEKEEPER_H
#define TIMEKEEPER_H

#include "windowmanager.h"

namespace timekeeper
{
    void timekeeping();
    void initialize();

    float getdeltatime();
    float gettimefactor();
};

#endif // TIMEKEEPER_H
