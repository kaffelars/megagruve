#include "consts.h"
#include "physicsobject.h"

#include "timekeeper.h"
#include "chunkcontroller.h"
#include "tiledata.h"
#include "physicsmanager.h"

physicsobject::physicsobject(wposition p, velocity v, point b, bbtype btyp, float gfactor)//std::vector<boundingbox::box>& fbbox)
{
    setvelocity(v);
    setposition(p);
    bbox = b;
    btype = btyp;
    gravityfactor = gfactor;

    resting = false;
    onfloor = false;

    falldamage = 0;
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

    for (int a = 0; a < 3; a++)
    {
        if (vel[a] > 0.9f) vel[a] = 0.9f;
        if (vel[a] < -0.9f) vel[a] = -0.9f;
    }
}

void physicsobject::stop()
{
    vel = velocity{0.0f,0.0f,0.0f};
}

void physicsobject::addvelocity(velocity v)
{
    vel += v;

    for (int a = 0; a < 3; a++)
    {
        if (vel[a] > 0.9f) vel[a] = 0.9f;
        if (vel[a] < -0.9f) vel[a] = -0.9f;
    }
}

void physicsobject::dophysics() //ha heller en egen func og ha physicsobject som lett container?
{
    physicsmanager::dophysics(*this);
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
    vel.y += 0.02f * gravityfactor * timekeeper::gettimefactor();//gravity lol

    if (vel.y > 0.9f) vel.y = 0.9f;

}
