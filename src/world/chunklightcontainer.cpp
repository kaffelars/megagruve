#include "consts.h"
#include "chunklightcontainer.h"
#include "utils.h"

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

uint8_t chunklightcontainer::getfirstlvalue(uint8_t val)
{
    return val >> 4;
}

uint8_t chunklightcontainer::getsecondlvalue(uint8_t val)
{
    return val & 15;
}

void chunklightcontainer::setfirstlvalue(uint8_t& refval, uint8_t val)
{
    refval = (refval & 15) | (val << 4);
}

void chunklightcontainer::setsecondlvalue(uint8_t& refval, uint8_t val)
{
    refval = (refval & 240) | val;
}

uint8_t chunklightcontainer::getlvalue(uint8_t layer, uint8_t x, uint8_t y, uint8_t z)
{
    if (x & 1)
        return getsecondlvalue(lightlayers[layer].light[(x/2) + 17 * (z + (34*y))]);
    else
        return getfirstlvalue(lightlayers[layer].light[(x/2) + 17 * (z + (34*y))]);

    //return lightlayers[layer].light[x + 34 * (z + (34*y))];

}

void chunklightcontainer::setlvalue(uint8_t layer, uint8_t x, uint8_t y, uint8_t z, uint8_t value)
{
    if (x & 1)
        setsecondlvalue(lightlayers[layer].light[(x/2) + 17 * (z + (34*y))], value);
    else
        setfirstlvalue(lightlayers[layer].light[(x/2) + 17 * (z + (34*y))], value);

    //lightlayers[layer].light[x + 34 * (z + (34*y))] = value;
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

void chunklightcontainer::getinterpolatedvalues(float x, float y, float z, uint8_t direction, uint8_t (&sunlight)[4])
{
    float totlight[4] = {0,0,0,0};
    int ex = 0, ey = 0, ez = 0;

    for (int a = 0; a < 3; a++)
    {
        for (int b = 0; b < 3; b++)
        {
            ex = x+a-1;
            ez = z+b-1;
            ey = y-1;

            //totlight += getvalue(ex, ey, ez);
        }
    }

    //return (uint8_t)(totlight / 4.0f);
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
    int ex = 0, ey = 0, ez = 0;

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
                ez = std::round(z) - b;
            }
            else
            {
                ex = std::round(x) - a;
                ey = std::round(y) - b;
                ez = int(z);
            }

            //std::cout << ex << " " << ey << " " << ez << "\n";

            totlight += getvalue(ex, ey, ez);
        }
    }

    return (uint8_t)(totlight / 4.0f);
}

uint8_t chunklightcontainer::getcorner(uint8_t x, uint8_t y, uint8_t z)
{
    uint8_t totlight = 0;
    uint8_t maxlight = 0;
    uint8_t lightval;

    for (int yy = 0; yy < 2; yy++)
    {
        for (int xx = 0; xx < 2; xx++)
        {
            for (int zz = 0; zz < 2; zz++)
            {
                lightval = getvalue(x - xx, y - yy , z - zz);
                totlight += lightval;
                if (lightval > maxlight) maxlight = lightval;
            }
        }
    }

    totlight = totlight / 4;
    if (totlight > maxlight) totlight = maxlight;
    return totlight;
}

uint8_t chunklightcontainer::getinterpolatedvalue2(float x, float y, float z)
{
    /*
    direction e.g. 0 = -x, 1 = x, osv.

    0,1: a = z, b = y
    2,3: a = x, b = z
    4,5: a = x, b = y
    */

    float totlight = 0;
    int ex = 0, ey = 0, ez = 0;

    ex = std::round(x);
    ey = std::round(y);
    ez = std::round(z);

    for (int yy = 0; yy < 2; yy++)
    {
        for (int xx = 0; xx < 2; xx++)
        {
            for (int zz = 0; zz < 2; zz++)
            {
                //std::cout << ex << " " << ey << " " << ez << "\n";

                totlight += getvalue(ex - xx, ey - yy , ez - zz);
            }
        }
    }

    totlight = totlight / 4.0f;
    utils::clamp(totlight, 0.0f, 15.0f);
    return (uint8_t)(totlight);
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
        lightlayers[layer].light = new uint8_t[17*34*4];
        uint8_t fillvalue = (lightlayers[layer].lightvalue << 4) + lightlayers[layer].lightvalue;
        //uint8_t fillvalue = lightlayers[layer].lightvalue;
        std::fill_n(lightlayers[layer].light, 17*34*4, fillvalue);
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
