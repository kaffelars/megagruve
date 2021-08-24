#include "consts.h"
#include "chunkgetvertexdata.h"

#include "chunkcoords.h"
#include "biomecontroller.h"

namespace chunkgetvertexdata
{
    uint8_t getambaround(chunk& c, ctilepos vertex, tiledata::tilesides ts);
    rgbcolor255 getbiomearound(chunk& c, chtilepos ctpos);
}

void chunkgetvertexdata::setambocc(chunk& c, ctilepos tilepos, tiledata::tilesides ts, uint8_t (&ambocc)[4])
{
    ctilepos around[4];

    chunkcoords::getvertexoffset(ts, around);

    for (int a = 0; a < 4; a++)
    {
        ambocc[a] = getambaround(c, tilepos + around[a], ts);
    }
}

void chunkgetvertexdata::setsunlight(chunk& c, ctilepos tilepos, tiledata::tilesides ts, uint8_t (&sunlight)[4])
{
    ctilepos around[4];

    chunkcoords::getvertexoffset(ts, around);

    for (int a = 0; a < 4; a++)
    {
        ctilepos above[4];

        chunkcoords::getabovetiles(ts, above);

        for (int b = 0; b < 4; b++)
        {
            uint8_t sl = c.getsunlight(tilepos + around[a] + above[b]);
            if (sl > sunlight[a]) sunlight[a] = sl;
        }
    }
}


uint8_t chunkgetvertexdata::getambaround(chunk& c, ctilepos vertex, tiledata::tilesides ts)
{
    uint8_t amb = 0;

    ctilepos above[4];

    chunkcoords::getabovetiles(ts, above);

    for (int a = 0; a < 4; a++)
    {
        int tilert = c.gettile(vertex + above[a]);
        if (tiledata::isambocc(tilert)) amb += 63;
    }

    if (amb) amb = 166;

    return amb;
}


void chunkgetvertexdata::getbiometintvertexes(chunk& c, chtilepos chtpos, tiledata::tilesides ts, rgbcolor255 (&rgb)[4])
{
    for (int a = 0; a < 4; a++)
        rgb[a] = rgbcolor255(0,0,0);

    chtilepos around[4];

    chunkcoords::getvertexoffset(ts, around);

    for (int a = 0; a < 4; a++)
    {
        rgb[a] = getbiomearound(c, chtpos + around[a]);
    }
}

rgbcolor255 chunkgetvertexdata::getbiomearound(chunk& c, chtilepos chtpos)
{
    rgbcolor255 r = rgbcolor255(0,0,0);

    for (int z = -1; z < 1; z++)
    {
        for (int x = -1; x < 1; x++)
        {
            r += biomecontroller::getbiometint(c.getbiome(chtilepos{chtpos.x+x, chtpos.y+z}));
        }
    }

    r.x = r.x / 4.0f;
    r.y = r.y / 4.0f;
    r.z = r.z / 4.0f;

    return r;
}
