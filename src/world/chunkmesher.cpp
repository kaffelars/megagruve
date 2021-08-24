#include "consts.h"
#include "chunkcontroller.h"

#include "biomecontroller.h"
#include "chunkcoords.h"
#include "chunkgetvertexdata.h"

namespace chunkcontroller
{
    //uint8_t getambaround(chunk& c, ctilepos vertex);
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

                tileid tid = c.gettile(ctilepos{x,y,z});

                if (!tiledata::isempty(tid))
                {
                    uint8_t sides = c.getsides(ctilepos{x,y,z});
                    //sunlight
                    uint8_t sunlight = 0;
                    uint8_t ambocc = 0;

                    if (y > 0)
                    {
                        for (int xx = -1; xx < 1; xx++)
                        {
                            for (int zz = -1; zz < 1; zz++)
                            {
                                ctilepos ct = ctilepos (x+xx, y-1, z+zz);
                                if (chunkcoords::withinchunkbounds(ct))
                                {
                                    uint8_t sunl = c.getsunlight(ct);
                                    //std::cout << int(sunl) << "o\n";
                                    if (sunl > sunlight) sunlight = sunl;
                                }
                            }
                        }

                        if (y < chunkheight-1)
                        {

                        }
                    }


                    tiledata::blockshape tileshape = tiledata::gettileshape(tid);
                    uint8_t glow = tiledata::gettileinfo(tid).glow;

                    if (tileshape == tiledata::SHAPE_BLOCK)
                    {
                        //bbb
                        uint8_t ambocc[4] = {0,0,0,0};
                        rgbcolor255 tint[4] = {rgbcolor255{255,255,255},rgbcolor255{255,255,255},rgbcolor255{255,255,255},rgbcolor255{255,255,255}};
                        rgbcolor255 light[4] = {rgbcolor255{0,0,0},rgbcolor255{0,0,0},rgbcolor255{0,0,0},rgbcolor255{0,0,0}};
                        uint8_t sunlight[4] = {0,0,0,0};

                        for (int a = 0; a < 6; a++)
                        {
                            if (sides & tiledata::sideflags[a])
                            {
                                chunkgetvertexdata::setambocc(c, ctilepos{x,y,z}, tiledata::sideflags[a], ambocc);
                                chunkgetvertexdata::setsunlight(c, ctilepos{x,y,z}, tiledata::sideflags[a], sunlight);

                                if (tiledata::gettileinfo(tid).biometint)
                                    chunkgetvertexdata::getbiometintvertexes(c, chtilepos{x,z}, tiledata::sideflags[a], tint);

                                if (tid == 1)
                                    tiledata::addside(ctilepos{x,y,z}, tid, 0, a, sunlight, light, glow, ambocc, tint, c.wmesh[cpart][c.getinactivemesh(cpart)]);
                                else
                                    tiledata::addside(ctilepos{x,y,z}, tid, 0, a, sunlight, light, glow, ambocc, tint, c.cmesh[cpart][c.getinactivemesh(cpart)]);
                            }
                        }
                    }
                    else
                    {
                        rgbcolor255 tint = rgbcolor255(255,255,255);

                        if (tiledata::gettileinfo(tid).biometint)
                            tint = biomecontroller::getbiometint(c.getbiome(chtilepos{x,z}));

                        tiledata::addblock(ctilepos{x,y,z}, tid, tileshape, sides, sunlight, rgbcolor255(0,0,0), glow, 0, tint, c.cmesh[cpart][c.getinactivemesh(cpart)]);
                    }
                }
            }
        }
    }
}



