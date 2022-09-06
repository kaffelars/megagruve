#include "consts.h"
#include "chunklight.h"

#include "tiledata.h"

namespace chunklight
{

}

void chunklight::generatesunlight(chunk& c) //initial full sunlight
{
    tileid tid = 0;
    int sunlightlayers = 0;
    int firstblocklayer = 0;

    for (ytile y = 0; y < chunkheight; y++) //combines
    {
        for (htile z = -1; z < chunkwidth+1; z++)
        {
            for (htile x = -1; x < chunkwidth+1; x++)
            {
                tid = c.gettile(ctilepos(x,y,z));
                if (tid != 0)
                {
                    if (tiledata::gettileinfo(tid).lightattenuation > 0)//hit first non fully transparent block
                    {
                        firstblocklayer = y;
                        goto nextstep; //evil goto!
                    }
                }
            }
        }
        sunlightlayers ++;
        if (sunlightlayers == 4)
        {
            sunlightlayers = 0;
            c.fillsunlayer(y/4, 255);
        }
    }

    nextstep:

    if ((firstblocklayer&3) != 0)
    {
        for (ytile y = firstblocklayer-(firstblocklayer&3); y < firstblocklayer; y++)
        {
            for (htile z = -1; z < chunkwidth+1; z++)
            {
                for (htile x = -1; x < chunkwidth+1; x++)
                {
                    c.setsunlight(ctilepos(x,y,z), 255);
                }
            }
        }
    }

    if (firstblocklayer > 0) //should never be false
    {
        //generate sunlight et al
        for (htile z = -1; z < chunkwidth+1; z++)
        {
            for (htile x = -1; x < chunkwidth+1; x++)
            {
                updatesunlight(c, ctilepos{x, firstblocklayer, z}, true);
            }
        }
    }
    else
    {
        std::cout << "(chunklight::generatesunlight) block(s) detected on y=0?!?!\n";
    }
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

        if (!initial) c.setremeshy(currentpos.y); //avoid remesh on chunk gen

        if (sunlight <= 0) break;
    }

}
