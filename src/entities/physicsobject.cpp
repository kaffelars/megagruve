#include "consts.h"
#include "physicsobject.h"

physicsobject::physicsobject(wposition p, velocity v, boundingbox::box b)//std::vector<boundingbox::box>& fbbox)
{
    setvelocity(v);
    setposition(p);
    bbox.changeboundingbox(b);
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
    return position + vel;
}

void physicsobject::updateposition()
{
    position += vel;
}

void physicsobject::updatevelocity()
{
    vel += velocity{0.0f,0.1f,0.0f};//gravity lol
}
