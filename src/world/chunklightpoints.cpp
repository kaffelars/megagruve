#include "consts.h"
#include "chunklightpoints.h"

chunklightpoints::chunklightpoints()
{
    //ctor
}

chunklightpoints::~chunklightpoints()
{
    //dtor
}

void chunklightpoints::addpoint(ctilepos ctpos, uint8_t lightstrength)
{
    lightpoints.push_back(lightpoint{ctpos, lightstrength});
    needspropagation = true;
}

bool chunklightpoints::requestspropagation()
{
    return needspropagation;
}

const std::vector<chunklightpoints::lightpoint>& chunklightpoints::getlightpoints()
{
    return lightpoints;
}

void chunklightpoints::propagated()
{
    needspropagation = false;
    for (lightpoint& l : lightpoints)
    {
        l.hasbeenpropagated =true;
    }
}
