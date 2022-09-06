#include "consts.h"
#include "chunklightcontainer.h"

chunklightcontainer::chunklightcontainer()
{
    //ctor
}

chunklightcontainer::~chunklightcontainer()
{
    //dtor
}

void chunklightcontainer::initialize()
{
    lightlayers.clear();
    for (uint8_t x = 0; x < 64; x++)
    {
        lightlayers.push_back(lightlayer{0, nullptr});
    }
}

void chunklightcontainer::deinitialize()
{
    for (uint8_t x = 0; x < 64; x++)
    {
        if (lightlayers[x].light != nullptr)
        {
            deallocate(x);
        }
    }
    lightlayers.clear();
}

uint8_t chunklightcontainer::getlvalue(uint8_t layer, uint8_t x, uint8_t y, uint8_t z)
{
    return lightlayers[layer].light[x + 34 * (z + (34*y))];
}

void chunklightcontainer::setlvalue(uint8_t layer, uint8_t x, uint8_t y, uint8_t z, uint8_t value)
{
    lightlayers[layer].light[x + 34 * (z + (34*y))] = value;
}

uint8_t chunklightcontainer::getvalue(uint8_t x, uint8_t y, uint8_t z)
{
    uint8_t layer = y / 4;
    if (lightlayers[layer].light == nullptr)
    {
        return lightlayers[layer].lightvalue;
    }
    y = y&3;
    return getlvalue(layer, x, y, z);
}

uint8_t chunklightcontainer::getvalue(ctilepos xyz)
{
    return getvalue(xyz.x, xyz.y, xyz.z);
}

uint8_t chunklightcontainer::getinterpolatedvalue(float x, float y, float z, uint8_t direction)
{
    /*
    direction e.g. 0 = -x, 1 = x, osv.

    0,1: a = z, b = y
    2,3: a = x, b = z
    4,5: a = x, b = y
    */

    float totlight = 0;
    int ex, ey, ez;

    for (int a = 0; a < 2; a++)
    {
        for (int b = 0; b < 2; b++)
        {
            if (direction < 2)
            {
                ex = int(x);
                ey = std::round(y) - a;
                ez = std::round(z) - b;
            }
            else if (direction < 4)
            {
                ex = std::round(x) - a;
                ey = int(y);
                ez = std::round(y) - b;
            }
            else
            {
                ex = std::round(x) - a;
                ey = std::round(y) - b;
                ez = int(z);
            }

            totlight += getvalue(ex, ey, ez);
        }
    }

    return (uint8_t)(totlight / 4.0f);
}

void chunklightcontainer::setvalue(uint8_t x, uint8_t y, uint8_t z, uint8_t value)
{
    uint8_t layer = y / 4;
    if (lightlayers[layer].light == nullptr)
    {
        allocate(layer);
    }
    y = y&3;
    setlvalue(layer, x, y, z, value);
}

void chunklightcontainer::setvalue(ctilepos xyz, uint8_t value)
{
    setvalue(xyz.x, xyz.y, xyz.z, value);
}

void chunklightcontainer::allocate(uint8_t layer)
{
    if (lightlayers[layer].light == nullptr)
    {
        lightlayers[layer].light = new uint8_t[34*34*4];
        std::fill_n(lightlayers[layer].light, 34*34*4, lightlayers[layer].lightvalue);
    }
}

void chunklightcontainer::deallocate(uint8_t layer)
{
    if (lightlayers[layer].light != nullptr)
    {
        delete[] lightlayers[layer].light;
        lightlayers[layer].light = nullptr;
    }
}

void chunklightcontainer::filllayer(uint8_t layer, uint8_t value)
{
    if (lightlayers[layer].light != nullptr)
    {
        deallocate(layer);
    }
    lightlayers[layer].lightvalue = value;
}
