#include "consts.h"
#include "chunkcontroller.h"

chunkpos chunkcontroller::wpostocpos(wposition wpos)
{
    chunkpos c = chunkpos(wpos.x/chunkwidth, wpos.z/chunkwidth);
    if (wpos.x < 0.0f) c.x -= 1;
    if (wpos.z < 0.0f) c.y -= 1;
    return c;
}

wposition chunkcontroller::cpostowpos(chunkpos cpos)
{
    wposition w = wposition(cpos.x * chunkwidth, 0, cpos.y * chunkwidth);
    return w;
}

chunkpos chunkcontroller::wtilepostocpos(wtilepos wtpos)
{
    return wpostocpos(wposition(wtpos));
}

wtilepos chunkcontroller::wpostowtilepos(wposition wpos)
{
    wtilepos w = wpos;
    if (wpos.x < 0.0f) w.x -= 1;
    if (wpos.z < 0.0f) w.z -= 1;
    if (wpos.y < 0) wpos.y = 0;
    if (wpos.y >= chunkheight) wpos.y = chunkheight - 1;
    return w;
}

ctilepos chunkcontroller::wpostoctilepos(wposition wpos)
{
    chunkpos c = wpostocpos(wpos);

    ctilepos t;
    t.y = wpos.y;
    if (t.y < 0) t.y = 0;
    if (t.y >= chunkheight) t.y = chunkheight - 1;
    t.x = wpos.x - (c.x * chunkwidth);
    t.z = wpos.z - (c.y * chunkwidth);

    //special border cases
    if (t.x == 32) t.x = 31;
    if (t.z == 32) t.z = 31;

    return t;
}

ctilepos chunkcontroller::wtilepostoctilepos(wtilepos wtpos)
{
    return wpostoctilepos(wposition(wtpos));
}
