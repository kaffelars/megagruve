#include "consts.h"
#include "chunkcoords.h"

chunkpos chunkcoords::wpostocpos(wposition wpos)
{
    chunkpos c = chunkpos(wpos.x/chunkwidth, wpos.z/chunkwidth);
    if (wpos.x < 0.0f) c.x -= 1;
    if (wpos.z < 0.0f) c.y -= 1;
    return c;
}

void chunkcoords::getabovetiles(tiledata::tilesides ts, ctilepos (&above)[4])
{
    switch (ts)
    {
    case tiledata::SIDE_XM:
        above[0] = ctilepos{-1,-1,0};
        above[1] = ctilepos{-1,-1,-1};
        above[2] = ctilepos{-1,0,-1};
        above[3] = ctilepos{-1,0,0};
        break;
    case tiledata::SIDE_XP:
        above[0] = ctilepos{0,-1,-1};
        above[1] = ctilepos{0,-1,0};
        above[2] = ctilepos{0,0,0};
        above[3] = ctilepos{0,0,-1};
        break;
    case tiledata::SIDE_YM:
        above[0] = ctilepos{-1,-1,-1};
        above[1] = ctilepos{0,-1,-1};
        above[2] = ctilepos{0,-1,0};
        above[3] = ctilepos{-1,-1,0};
        break;
    case tiledata::SIDE_YP:
        above[0] = ctilepos{-1,0,-1};
        above[1] = ctilepos{0,0,-1};
        above[2] = ctilepos{0,0,0};
        above[3] = ctilepos{-1,0,0};
        break;
    case tiledata::SIDE_ZM:
        above[0] = ctilepos{-1,-1,-1};
        above[1] = ctilepos{0,-1,-1};
        above[2] = ctilepos{0,0,-1};
        above[3] = ctilepos{-1,0,-1};
        break;
    case tiledata::SIDE_ZP:
        above[0] = ctilepos{0,-1,0};
        above[1] = ctilepos{-1,-1,0};
        above[2] = ctilepos{-1,0,0};
        above[3] = ctilepos{0,0,0};
        break;
    }
}

void chunkcoords::getvertexoffset(tiledata::tilesides ts, chtilepos (&around)[4])
{
    switch (ts)
    {
    case tiledata::SIDE_XM:
        around[0] = chtilepos{0,1};
        around[1] = chtilepos{0,0};
        around[2] = chtilepos{0,0};
        around[3] = chtilepos{0,1};
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
        around[0] = chtilepos{1,1};
        around[1] = chtilepos{0,1};
        around[2] = chtilepos{0,1};
        around[3] = chtilepos{1,1};
        break;
    }
}

void chunkcoords::getvertexoffset(tiledata::tilesides ts, ctilepos (&around)[4])
{
    switch (ts)
    {
    case tiledata::SIDE_XM:
        around[0] = ctilepos{0,0,1};
        around[1] = ctilepos{0,0,0};
        around[2] = ctilepos{0,1,0};
        around[3] = ctilepos{0,1,1};
        break;
    case tiledata::SIDE_XP:
        around[0] = ctilepos{1,0,0};
        around[1] = ctilepos{1,0,1};
        around[2] = ctilepos{1,1,1};
        around[3] = ctilepos{1,1,0};
        break;
    case tiledata::SIDE_YM:
        around[0] = ctilepos{0,0,0};
        around[1] = ctilepos{1,0,0};
        around[2] = ctilepos{1,0,1};
        around[3] = ctilepos{0,0,1};
        break;
    case tiledata::SIDE_YP:
        around[0] = ctilepos{0,1,0};
        around[1] = ctilepos{1,1,0};
        around[2] = ctilepos{1,1,1};
        around[3] = ctilepos{0,1,1};
        break;
    case tiledata::SIDE_ZM:
        around[0] = ctilepos{0,0,0};
        around[1] = ctilepos{1,0,0};
        around[2] = ctilepos{1,1,0};
        around[3] = ctilepos{0,1,0};
        break;
    case tiledata::SIDE_ZP:
        around[0] = ctilepos{1,0,1};
        around[1] = ctilepos{0,0,1};
        around[2] = ctilepos{0,1,1};
        around[3] = ctilepos{1,1,1};
        break;
    }
}

bool chunkcoords::withinchunkbounds(ctilepos cpos)
{
    if (cpos.x < 0 || cpos.x > chunkwidth-1) return false;
    if (cpos.y < 0 || cpos.y > chunkheight-1) return false;
    if (cpos.z < 0 || cpos.z > chunkwidth-1) return false;
    return true;
}

bool chunkcoords::withinextendedchunkbounds(ctilepos cpos)
{
    if (cpos.x < -1 || cpos.x > chunkwidth) return false;
    if (cpos.y < -1 || cpos.y > chunkheight) return false;
    if (cpos.z < -1 || cpos.z > chunkwidth) return false;
    return true;
}

wtilepos chunkcoords::cposctilepostowtilepos(chunkpos cpos, ctilepos ctpos)
{
    return wtilepos{cpos.x * chunkwidth + ctpos.x, ctpos.y, ctpos.z + cpos.y * chunkwidth};
}

wposition chunkcoords::cpostowpos(chunkpos cpos)
{
    wposition w = wposition(cpos.x * chunkwidth, 0, cpos.y * chunkwidth);
    return w;
}

chunkpos chunkcoords::wtilepostocpos(wtilepos wtpos)
{
    return wpostocpos(wposition(wtpos));
}

wtilepos chunkcoords::wpostowtilepos(wposition wpos)
{
    wtilepos w = wpos;
    if (ceilf(wpos.x) != wpos.x && wpos.x < 0.0f) w.x -= 1;
    if (ceilf(wpos.z) != wpos.z && wpos.z < 0.0f) w.z -= 1;
    if (wpos.y < 0) wpos.y = 0;
    if (wpos.y >= chunkheight) wpos.y = chunkheight - 1;
    return w;
}

ctilepos chunkcoords::wpostoctilepos(wposition wpos) //noe er galt her med negative pos
{
    chunkpos c = wpostocpos(wpos);

    ctilepos t;
    t.y = wpos.y;
    if (t.y < 0) t.y = 0;
    if (t.y >= chunkheight) t.y = chunkheight - 1;
    t.x = wpos.x - (c.x * chunkwidth);
    t.z = wpos.z - (c.y * chunkwidth);

    /*if (wpos.x < 0) t.x+=1;
    if (wpos.z < 0) t.z+=1;*/

    //special border cases
    if (t.x == 32) t.x = 31;
    if (t.z == 32) t.z = 31;

    return t;
}

ctilepos chunkcoords::wtilepostoctilepos(wtilepos wtpos)
{
    return wpostoctilepos(wposition(wtpos));
}

bool chunkcoords::wtileposwithinworldbounds(wtilepos wtpos)
{
    if (wtpos.y >= 0 && wtpos.y < chunkheight) return true;
    return false;
}
