#include "consts.h"
#include "chunklight.h"

#include "tiledata.h"

namespace chunklight
{

}

void chunklight::generatesunlight(chunk& c)
{
    for (htile z = -1; z < chunkwidth+1; z++)
    {
        for (htile x = -1; x < chunkwidth+1; x++)
        {
            c.setsunlight(ctilepos(x,0,z), 255);
        }
    }

    //generate sunlight et al
    for (htile z = -1; z < chunkwidth+1; z++)
    {
        for (htile x = -1; x < chunkwidth+1; x++)
        {
            updatesunlight(c, ctilepos{x, 1, z}, true);
        }
    }
    //
}

void chunklight::updatesunlight(chunk& c, ctilepos ctpos, bool initial) //dette funker bare av og til
{
    //chunkexists guard? neh
    //messy stuff
    if (ctpos.y <= 0) return;
    ctilepos currentpos = ctilepos{ctpos.x,ctpos.y-1, ctpos.z};
    int32_t sunlight = c.getsunlight(currentpos);
    if (sunlight == 0) return;

    uint8_t oldsunlight = c.getsunlight(currentpos);

    while (oldsunlight > 0)
    {
        tileid tid = c.gettile(currentpos);

        //duplicated no good
        if (tiledata::gettiletype(tid) == tiledata::T_SOLID)
            sunlight = 0;
        if (tiledata::gettiletype(tid) == tiledata::T_TRANSPARENT)
            sunlight -= 16;
        if (tiledata::gettiletype(tid) == tiledata::T_WATER)
            sunlight -= 64;
        if (tiledata::gettiletype(tid) == tiledata::T_DISCARD)
            sunlight -= 32;
        if (tiledata::gettiletype(tid) == tiledata::T_OBJECT)
            sunlight -= 16;

        if (sunlight < 0) sunlight = 0;

        if (initial)
            oldsunlight = sunlight;
        else
            oldsunlight = c.getsunlight(currentpos);

        c.setsunlight(currentpos, sunlight);

        if (!initial) c.setremeshy(currentpos.y);

        currentpos.y++;
        if (currentpos.y == chunkheight) break;
    }


}
