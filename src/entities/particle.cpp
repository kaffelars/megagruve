#include "consts.h"
#include "particle.h"

particle::particle(wposition p, velocity v, uint8_t ptex, uint8_t psiz, uint32_t dur, uint8_t glo) : physicsobject(p, v, point(0,0,0), physicsobject::BB_POINT, 0.1f)
{
    textureid = ptex;
    particlesize = psiz;
    duration = dur;
    glow = glo;
}

particle::~particle()
{
    //dtor
}
