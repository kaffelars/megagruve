#include "consts.h"
#include "chunkcontroller.h"

namespace chunkcontroller
{
    uint8_t getambaround(chunk& c, ctilepos vertex);
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
                                if (withinchunkbounds(ct))
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
                        if (sides & tiledata::SIDE_XM)
                        {
                            ambocc[0] = getambaround(c, ctilepos{x,y,z});
                            ambocc[1] = getambaround(c, ctilepos{x,y,z+1});
                            ambocc[2] = getambaround(c, ctilepos{x,y+1,z+1});
                            ambocc[3] = getambaround(c, ctilepos{x,y+1,z});
                            tiledata::addside(ctilepos{x,y,z}, tid, 0, 0, sunlight, rgbcolor255(0,0,0), glow, ambocc, c.cmesh[cpart][c.getinactivemesh(cpart)]);
                        }
                        if (sides & tiledata::SIDE_XP)
                        {
                            ambocc[0] = getambaround(c, ctilepos{x+1,y,z});
                            ambocc[1] = getambaround(c, ctilepos{x+1,y,z+1});
                            ambocc[2] = getambaround(c, ctilepos{x+1,y+1,z+1});
                            ambocc[3] = getambaround(c, ctilepos{x+1,y+1,z});
                            tiledata::addside(ctilepos{x,y,z}, tid, 0, 1, sunlight, rgbcolor255(0,0,0), glow, ambocc, c.cmesh[cpart][c.getinactivemesh(cpart)]);
                        }
                        if (sides & tiledata::SIDE_YM)
                        {
                            ambocc[0] = getambaround(c, ctilepos{x,y,z});
                            ambocc[1] = getambaround(c, ctilepos{x+1,y,z});
                            ambocc[2] = getambaround(c, ctilepos{x+1,y,z+1});
                            ambocc[3] = getambaround(c, ctilepos{x,y,z+1});
                            tiledata::addside(ctilepos{x,y,z}, tid, 0, 2, sunlight, rgbcolor255(0,0,0), glow, ambocc, c.cmesh[cpart][c.getinactivemesh(cpart)]);
                        }
                        if (sides & tiledata::SIDE_YP)
                        {
                            ambocc[0] = getambaround(c, ctilepos{x,y+1,z});
                            ambocc[1] = getambaround(c, ctilepos{x+1,y+1,z});
                            ambocc[2] = getambaround(c, ctilepos{x+1,y+1,z+1});
                            ambocc[3] = getambaround(c, ctilepos{x,y+1,z+1});
                            tiledata::addside(ctilepos{x,y,z}, tid, 0, 3, sunlight, rgbcolor255(0,0,0), glow, ambocc, c.cmesh[cpart][c.getinactivemesh(cpart)]);
                        }
                        if (sides & tiledata::SIDE_ZM)
                        {
                            ambocc[0] = getambaround(c, ctilepos{x,y,z});
                            ambocc[1] = getambaround(c, ctilepos{x+1,y,z});
                            ambocc[2] = getambaround(c, ctilepos{x+1,y+1,z});
                            ambocc[3] = getambaround(c, ctilepos{x,y+1,z});
                            tiledata::addside(ctilepos{x,y,z}, tid, 0, 4, sunlight, rgbcolor255(0,0,0), glow, ambocc, c.cmesh[cpart][c.getinactivemesh(cpart)]);
                        }
                        if (sides & tiledata::SIDE_ZP)
                        {
                            ambocc[0] = getambaround(c, ctilepos{x,y,z+1});
                            ambocc[1] = getambaround(c, ctilepos{x+1,y,z+1});
                            ambocc[2] = getambaround(c, ctilepos{x+1,y+1,z+1});
                            ambocc[3] = getambaround(c, ctilepos{x,y+1,z+1});
                            tiledata::addside(ctilepos{x,y,z}, tid, 0, 5, sunlight, rgbcolor255(0,0,0), glow, ambocc, c.cmesh[cpart][c.getinactivemesh(cpart)]);
                        }
                    }
                    else
                    {
                        tiledata::addblock(ctilepos{x,y,z}, tid, tileshape, sides, sunlight, rgbcolor255(0,0,0), glow, 0, c.cmesh[cpart][c.getinactivemesh(cpart)]);
                    }
                }
            }
        }
    }
}

uint8_t chunkcontroller::getambaround(chunk& c, ctilepos vertex)
{
    uint8_t amb = 0;
    for (ytile y = vertex.y-1; y < vertex.y+1; y++)
    {
        for (htile z = vertex.z-1; z < vertex.z+1; z++)
        {
            for (htile x = vertex.x-1; x < vertex.x+1; x++)
            {
                int tilert = c.gettile(ctilepos{x,y,z});
                if (tiledata::isambocc(tilert)) amb += 1;
            }
        }
    }
    return amb;
}
