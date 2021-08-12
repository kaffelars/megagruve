#include "consts.h"
#include "chunkcontroller.h"

namespace chunkcontroller
{

}

void chunkcontroller::meshwholechunk(chunk& c)
{
    for (int a = 0; a < chunkmeshynum; a++)
    {
        meshchunkpart(c, a);
    }

    threadcounter--;

    c.settag(chunk::C_MESHED);
}

void chunkcontroller::remeshchunk(chunk& c)
{
    for (int a = 0; a < chunkmeshynum; a++)
    {
        if (c.getremesh(a))
        {
            meshchunkpart(c, a);
        }
    }

    threadcounter--;

    c.settag(chunk::C_REMESHED);
}

void chunkcontroller::meshchunkpart(chunk& c, uint8_t cpart)
{
    //dimensions dims = c.cdims;

    ytile starty = cpart * chunkmeshheight;
    ytile endy = (cpart + 1) * chunkmeshheight;

    //std::cout << int(cpart) << " - " << int(starty) << "x" << int(endy) << "\n";

    //std::cout << int(c.getactivemesh(cpart));


    for (ytile y = starty; y < endy; y++)
    {
        for (htile z = 0; z < chunkwidth; z++)
        {
            for (htile x = 0; x < chunkwidth; x++)
            {
                uint8_t sides = c.getsides(ctilepos{x,y,z});
                tileid tid = c.gettile(ctilepos{x,y,z});

                //sunlight
                uint8_t sunlight = 0;

                if (y > 0)
                {
                    for (int xx = -1; xx < 1; xx++)
                    {
                        for (int zz = -1; zz < 1; zz++)
                        {
                            ctilepos ct = ctilepos (x+xx, y-1, z+zz);
                            if (withinchunkbounds(ct))
                            {
                                uint8_t sunl = c.getsunlight(ct);
                                //std::cout << int(sunl) << "o\n";
                                if (sunl > sunlight) sunlight = sunl;
                            }
                        }
                    }
                }


                uint8_t tileshape = tiledata::gettileshape(tid);



                tiledata::addblock(ctilepos{x,y,z}, tid, tileshape, sides, sunlight, rgbcolor255(0,0,0), c.cmesh[cpart][c.getinactivemesh(cpart)]);
            }
        }
    }
}
