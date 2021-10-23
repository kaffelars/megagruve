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
    if (ctpos.y <= 0) return;
    ctilepos currentpos = ctilepos{ctpos.x,ctpos.y-1, ctpos.z};
    int32_t sunlight = c.getsunlight(currentpos);
    if (sunlight == 0) return;

    while (true)
    {
        currentpos.y ++;
        if (currentpos.y == chunkheight) break;
        tileid tid = c.gettile(currentpos);
        uint8_t lightattenuation = tiledata::gettileinfo(tid).lightattenuation;

        sunlight -= lightattenuation;
        if (sunlight <0) sunlight=0;

        c.setsunlight(currentpos, sunlight);

        if (!initial) c.setremeshy(currentpos.y); //for å unngå at remesh trigges når chunk genereres

        if (sunlight <= 0) break;
    }

}
