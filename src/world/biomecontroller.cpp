#include "consts.h"

#include "biomecontroller.h"
#include "texturemanager.h"

namespace biomecontroller
{
    rgbcolor255 getbiomearound(chunk& c, chtilepos ctpos);

    std::vector<rgbcolor255> biometintcolors;
}

void biomecontroller::initialize()
{
    texturemanager::getbiometint(biometintcolors);
}

rgbcolor255 biomecontroller::getbiometint(chunk::biomedata b)
{
    return biometintcolors[b.humidity + 256 * b.temperature];
}

void biomecontroller::getbiometintvertexes(chunk& c, chtilepos chtpos, tiledata::tilesides ts, rgbcolor255 (&rgb)[4])
{
    for (int a = 0; a < 4; a++)
        rgb[a] = rgbcolor255(0,0,0);

    chtilepos around[4];

    switch (ts)
    {
    case tiledata::SIDE_XM:
        around[0] = chtilepos{0,0};
        around[1] = chtilepos{0,1};
        around[2] = chtilepos{0,1};
        around[3] = chtilepos{0,0};
        break;
    case tiledata::SIDE_XP:
        around[0] = chtilepos{1,0};
        around[1] = chtilepos{1,1};
        around[2] = chtilepos{1,1};
        around[3] = chtilepos{1,0};
        break;
    case tiledata::SIDE_YM:
        around[0] = chtilepos{0,0};
        around[1] = chtilepos{1,0};
        around[2] = chtilepos{1,1};
        around[3] = chtilepos{0,1};
        break;
    case tiledata::SIDE_YP:
        around[0] = chtilepos{0,0};
        around[1] = chtilepos{1,0};
        around[2] = chtilepos{1,1};
        around[3] = chtilepos{0,1};
        break;
    case tiledata::SIDE_ZM:
        around[0] = chtilepos{0,0};
        around[1] = chtilepos{1,0};
        around[2] = chtilepos{1,0};
        around[3] = chtilepos{0,0};
        break;
    case tiledata::SIDE_ZP:
        around[0] = chtilepos{0,1};
        around[1] = chtilepos{1,1};
        around[2] = chtilepos{1,1};
        around[3] = chtilepos{0,1};
        break;
    }

    for (int a = 0; a < 4; a++)
    {
        rgb[a] = getbiomearound(c, chtpos + around[a]);
    }
}

rgbcolor255 biomecontroller::getbiomearound(chunk& c, chtilepos chtpos)
{
    rgbcolor255 r = rgbcolor255(0,0,0);

    for (int z = -1; z < 1; z++)
    {
        for (int x = -1; x < 1; x++)
        {
            r += getbiometint(c.getbiome(chtilepos{chtpos.x+x, chtpos.y+z}));
        }
    }

    r.x = r.x / 4.0f;
    r.y = r.y / 4.0f;
    r.z = r.z / 4.0f;

    return r;
}
