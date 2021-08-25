#include "consts.h"
#include "physicsobject.h"

#include "timekeeper.h"

physicsobject::physicsobject(wposition p, velocity v, point b, bbtype btyp, float gfactor)//std::vector<boundingbox::box>& fbbox)
{
    setvelocity(v);
    setposition(p);
    bbox = b;
    btype = btyp;
    gravityfactor = gfactor;
}

physicsobject::physicsobject() = default;

physicsobject::~physicsobject()
{
    //dtor
}

wposition physicsobject::getposition()
{
    return position;
}

void physicsobject::setposition(wposition p)
{
    position = p;
}

void physicsobject::addposition(wposition p)
{
    position += p;
}

void physicsobject::setvelocity(velocity v)
{
    vel = v;
}

void physicsobject::stop()
{
    vel = velocity{0.0f,0.0f,0.0f};
}

void physicsobject::addvelocity(velocity v)
{
    vel += v;
}

wposition physicsobject::getnextposition()
{
    return position + vel * timekeeper::gettimefactor();
}

void physicsobject::updateposition()
{
    position += vel * timekeeper::gettimefactor();
}

void physicsobject::updatevelocity()
{
    vel += velocity{0.0f,0.1f * gravityfactor,0.0f};//gravity lol
}
