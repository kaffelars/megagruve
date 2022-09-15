#include "consts.h"
#include "chunkgetvertexdata.h"

#include "chunkcoords.h"
#include "biomecontroller.h"

namespace chunkgetvertexdata
{
    uint8_t getambaround(chunk& c, ctilepos vertex, tiledata::tilesides ts);
    rgbcolor255 getbiomearound(chunk& c, ctilepos ctpos);
}

void chunkgetvertexdata::setambocc(chunk& c, ctilepos tilepos, tiledata::tilesides ts, uint8_t (&ambocc)[4])
{
    if (tilepos.y == 0 || tilepos.y == chunkheight-1)
    {
        for (int a = 0; a < 4; a++)
        {
            ambocc[a] = 0;
        }
        return;
    }

    ctilepos around[4];

    chunkcoords::getvertexoffset(ts, around);

    for (int a = 0; a < 4; a++)
    {
        ambocc[a] = getambaround(c, tilepos + around[a], ts);
    }
}

void chunkgetvertexdata::setsunlight(chunk& c, ctilepos tilepos, tiledata::tilesides ts, uint8_t (&sunlight)[4])
{
    if (tilepos.y == 0)
    {
        for (int a = 0; a < 4; a++)
        {
            sunlight[a] = 255;
        }
        return;
    }

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
    if (vertex.y == 0) return 0;

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

uint8_t chunkgetvertexdata::getambocc(chunk& c, ctilepos vertex)
{
    uint8_t ambocc = 0;

    for (int yy = 0; yy < 2; yy++)
    {
        for (int xx = 0; xx < 2; xx++)
        {
            for (int zz = 0; zz < 2; zz++)
            {
                if (!tiledata::isambocc(c.gettile(vertex + ctilepos(-xx, -yy, -zz)))) ambocc += 15;
                if (ambocc >= 60) return 15;
            }
        }
    }

    ambocc /= 4;
    if (ambocc > 15) ambocc = 15;

    return ambocc;
}


void chunkgetvertexdata::getbiometintvertexes(chunk& c, ctilepos ctpos, tiledata::tilesides ts, rgbcolor255 (&rgb)[4])
{
    for (int a = 0; a < 4; a++)
        rgb[a] = rgbcolor255(0,0,0);

    chtilepos around[4];

    chunkcoords::getvertexoffset(ts, around);

    for (int a = 0; a < 4; a++)
    {
        rgb[a] = getbiomearound(c, ctpos + ctilepos{around[a].x, 0, around[a].y});
    }
}

void chunkgetvertexdata::getbiometintvertex(chunk& c, ctilepos vertexpos, rgbcolor255& rgb)
{
    rgb = getbiomearound(c, vertexpos);
}

rgbcolor255 chunkgetvertexdata::getbiomearound(chunk& c, ctilepos ctpos)
{
    rgbcolor255 r = rgbcolor255(0,0,0);

    for (int z = -1; z < 1; z++)
    {
        for (int x = -1; x < 1; x++)
        {
            r += biomecontroller::getbiometint(c.getbiome(ctilepos{ctpos.x+x, ctpos.y, ctpos.z+z}));
        }
    }

    r.x = r.x / 4.0f;
    r.y = r.y / 4.0f;
    r.z = r.z / 4.0f;

    return r;
}
