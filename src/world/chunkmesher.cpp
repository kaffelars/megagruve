#include "consts.h"
#include "chunkcontroller.h"

#include "biomecontroller.h"
#include "chunkcoords.h"
#include "chunkgetvertexdata.h"
#include "tileshape.h"

namespace chunkcontroller
{
    //uint8_t getambaround(chunk& c, ctilepos vertex);
}

void chunkcontroller::meshwholechunk(chunk& c)
{
    //std::cout << "meshin";
    for (int a = 0; a < chunkmeshynum; a++)
    {
        meshchunkpart2(c, a);
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
            meshchunkpart2(c, a);
        }
    }

    threadcounter--;

    c.settag(chunk::C_REMESHED);
}

void chunkcontroller::meshchunkpart2(chunk& c, uint8_t cpart)
{
    ytile starty = cpart * chunkmeshheight;
    ytile endy = (cpart + 1) * chunkmeshheight;

    rgbcolor255 tint = notint;
    tileid neighbour;
    uint8_t glow;
    tiledata::blockshape tshape;
    tileid tid;
    uint8_t sunlight;
    uint8_t tilelight;
    uint8_t ambocc;

    uint32_t texid;
    uint32_t overlayid;

    float corners[4];

    vpos datavpos;
    vpos vertexpos;
    vnorm datanorm;
    uvpos datauv;

    const std::vector<tileshape>& tileshapes = tiledata::gettileshapesdata();


    for (ytile y = starty; y < endy; y++)
    {
        for (htile z = 0; z < chunkwidth; z++)
        {
            for (htile x = 0; x < chunkwidth; x++)
            {
                tid = c.gettile(ctilepos{x,y,z});

                if (tid == 255) //map_obj
                {
                    c.getmapobj(ctilepos{x,y,z})->addmodel(ctilepos{x,y,z}, c.cmesh[cpart][c.getinactivemesh(cpart)], c.sunlight, c.tilelight);
                }
                else if (!tiledata::isempty(tid))
                {
                    tshape = tiledata::gettileshape(tid);
                    glow = tiledata::gettileinfo(tid).glow;
                    //tint = {notint,notint,notint,notint};

                    if (tiledata::iswater(tid) && y > 0) //water
                    {
                        if (tiledata::isflowingwater(tid))
                        {
                            chunkgetvertexdata::setwatercornersheight(c, ctilepos(x,y,z), corners);
                        }
                        else
                        {
                            if (tiledata::iswater(c.gettile(ctilepos(x,y-1,z))))
                            {
                                corners[0] = 0.0f;
                                corners[1] = 0.0f;
                                corners[2] = 0.0f;
                                corners[3] = 0.0f;
                            }
                            else
                            {
                                corners[0] = 0.1f;
                                corners[1] = 0.1f;
                                corners[2] = 0.1f;
                                corners[3] = 0.1f;
                            }
                        }

                    }
                    //water end

                    for (int a = 0; a < 7; a++)
                    {
                        if (tileshapes[tshape].hasside[a])
                        {
                            if (a == 6 || (y + sideoffsets[a].y > 0 && y + sideoffsets[a].y < 255))
                            {
                                if (a < 6) neighbour = c.gettile(ctilepos{x,y,z} + sideoffsets[a]);

                                if (a == 6 || tiledata::renderside(tid, neighbour, a))
                                {
                                    texid = tiledata::gettileinfo(tid).sidetextureids[a == 6 ? 0:a];
                                    overlayid = tiledata::gettileinfo(tid).overlaytextureids[a == 6 ? 0:a];


                                    while (texid)
                                    {
                                        for (int b = 0; b < tileshapes[tshape].vertexes[a].size(); b++)
                                        {
                                            vertexpos = tileshapes[tshape].vertexes[a][b];
                                            datavpos = vertexpos + vpos{x,y,z};
                                            datauv = tileshapes[tshape].uv[a][b];

                                            if (a == 6)
                                            {
                                                datanorm = tileshapes[tshape].normals[b];
                                            }
                                            else
                                            {
                                                datanorm = sideoffsets[a];
                                            }


                                            if (tiledata::gettileinfo(tid).biometint && !overlayid)
                                                chunkgetvertexdata::getbiometintvertex(c, ctilepos{datavpos.x,datavpos.y,datavpos.z}, tint);
                                            else
                                                tint = notint;

                                            //sunlight = c.getsunlight(ctilepos{x,y,z});
                                            //std::cout << int(x) << " " << int(y) << " " << int(z) << "\n";
                                            //sunlight = c.getinterpolatedsunlight(datavpos.x+(datanorm.x/2.0f),datavpos.y+(datanorm.y/2.0f),datavpos.z+(datanorm.z/2.0f),a);
                                            ctilepos corner = glm::ivec3(std::round(datavpos.x), std::round(datavpos.y), std::round(datavpos.z));
                                            sunlight = c.getsunlightcorner(corner.x,corner.y,corner.z);
                                            tilelight = c.gettilelightcorner(corner.x,corner.y,corner.z);
                                            ambocc = chunkgetvertexdata::getambocc(c, corner);

                                            if (tiledata::iswater(tid))
                                            {
                                                if (vertexpos.y < 0.5f)
                                                {
                                                    if (vertexpos.x < 0.5f && vertexpos.z < 0.5f) vertexpos.y = corners[0];
                                                    if (vertexpos.x > 0.5f && vertexpos.z < 0.5f) vertexpos.y = corners[1];
                                                    if (vertexpos.x < 0.5f && vertexpos.z > 0.5f) vertexpos.y = corners[2];
                                                    if (vertexpos.x > 0.5f && vertexpos.z > 0.5f) vertexpos.y = corners[3];
                                                }

                                                vertexpos += vpos{x,y,z};
                                                c.wmesh[cpart][c.getinactivemesh(cpart)].
                                                addvertex(vertexpos, datanorm, datauv, texid, sunlight, tilelight, glow, ambocc, tint);
                                            }
                                            else
                                            {
                                                c.cmesh[cpart][c.getinactivemesh(cpart)].
                                                addvertex(datavpos, datanorm, datauv, texid, sunlight, tilelight, glow, ambocc, tint);
                                            }
                                        }

                                        texid = overlayid;
                                        overlayid = 0;
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/*void chunkcontroller::meshchunkpart(chunk& c, uint8_t cpart)
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

                if (tid == 255) //map_obj
                {
                    c.getmapobj(ctilepos{x,y,z})->addmodel(ctilepos{x,y,z}, c.cmesh[cpart][c.getinactivemesh(cpart)], c.sunlight);
                }
                else if (!tiledata::isempty(tid))
                {
                    //sunlight
                    uint8_t sunlight = 0;
                    //uint8_t ambocc = 0;

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
                        rgbcolor255 tint[4] = {notint,notint,notint,notint};
                        rgbcolor255 light[4] = {rgbcolor255{0,0,0},rgbcolor255{0,0,0},rgbcolor255{0,0,0},rgbcolor255{0,0,0}};
                        uint8_t sunlight[4] = {0,0,0,0};

                        for (int a = 0; a < 6; a++)
                        {
                            tileid neighbour = 2;
                            if (y + sideoffsets[a].y >= 0 && y + sideoffsets[a].y < chunkheight) neighbour = c.gettile(ctilepos{x,y,z} + sideoffsets[a]);

                            if (tiledata::renderside(tid, neighbour, a))
                            {
                                chunkgetvertexdata::setambocc(c, ctilepos{x,y,z}, tiledata::sideflags[a], ambocc);
                                chunkgetvertexdata::setsunlight(c, ctilepos{x,y,z}, tiledata::sideflags[a], sunlight);

                                if (tiledata::gettileinfo(tid).biometint)
                                    chunkgetvertexdata::getbiometintvertexes(c, ctilepos{x,y,z}, tiledata::sideflags[a], tint);

                                if (tid == 1)
                                {
                                    tiledata::addside(ctilepos{x,y,z}, tid, 0, a, sunlight, light, glow, ambocc, tint, c.wmesh[cpart][c.getinactivemesh(cpart)]);
                                    if (a == 2)
                                        tiledata::addside(ctilepos{x,y-1,z}, tid, 0, 3, sunlight, light, glow, ambocc, tint, c.wmesh[cpart][c.getinactivemesh(cpart)]); //water underside
                                }
                                else
                                    tiledata::addside(ctilepos{x,y,z}, tid, 0, a, sunlight, light, glow, ambocc, tint, c.cmesh[cpart][c.getinactivemesh(cpart)]);

                            }
                        }
                    }
                    else
                    {
                        uint8_t tilesides = 0;
                        if (tileshape == tiledata::SHAPE_CACTUS)
                        {
                            for (int a = 0; a < 6; a++)
                            {
                                tileid neighbour = 2;
                                if (y > 0 && y < chunkheight-1) neighbour = c.gettile(ctilepos{x,y,z} + sideoffsets[a]);

                                if (tiledata::renderside(tid, neighbour, a))
                                {
                                    tilesides = tilesides | sideflags[a];
                                }
                            }
                        }

                        rgbcolor255 tint = notint;

                        if (tiledata::gettileinfo(tid).biometint)
                            tint = biomecontroller::getbiometint(c.getbiome(chtilepos{x,z}));

                        tiledata::addblock(ctilepos{x,y,z}, tid, tileshape, tilesides, sunlight, rgbcolor255(0,0,0), glow, 0, tint, c.cmesh[cpart][c.getinactivemesh(cpart)]);
                    }
                }
            }
        }
    }
}*/



