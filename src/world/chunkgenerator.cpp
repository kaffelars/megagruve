#include "consts.h"
#include "chunkcontroller.h"

#include "chunkcoords.h"

namespace chunkcontroller
{
    tiledata::tilesides sides[6] = {tiledata::SIDE_XM, tiledata::SIDE_XP, tiledata::SIDE_YM, tiledata::SIDE_YP, tiledata::SIDE_ZM, tiledata::SIDE_ZP};
}

void chunkcontroller::generatechunk(chunk& c)
{
    dimensions dims = c.cdims;
    chunkpos cposoffset = c.cpos;
    cposoffset.x *= chunkwidth;
    cposoffset.y *= chunkwidth;

    //biomes
    for (int32_t a = 0; a < (chunkwidth+1)*(chunkwidth+1); a++)
        c.addbiome();

    for (htile z = -1; z < chunkwidth+1; z++)
    {
        for (htile x = -1; x < chunkwidth+1; x++)
        {
            uint8_t temp = 127;
            uint8_t humid = 127;

            float tempnoise = (randfunc::noise(x + cposoffset.x +123, -321, z + cposoffset.y-3452, 793.3f)) * 175.0f;
            float humidnoise = (randfunc::noise(x + cposoffset.x +564, 221, z + cposoffset.y+391, 813.3f)) * 175.0f;

            utils::clamp(tempnoise, -127.0f, 128.0f);
            utils::clamp(humidnoise, -127.0f, 128.0f);

            temp += tempnoise;
            humid += humidnoise;

            c.setbiome(chunk::biomedata{temp, humid}, chtilepos{x,z});
        }
    }

    tileid tid_grass = tiledata::gettileid("t_grass");
    tileid tid_grass2 = tiledata::gettileid("t_grass2");

    tileid tid_dirt = tiledata::gettileid("t_dirt");

    tileid tid_sand = tiledata::gettileid("t_sand");
    tileid tid_rock = tiledata::gettileid("t_rock");

    tileid tid_snow = tiledata::gettileid("t_snow");
    tileid tid_gravel = tiledata::gettileid("t_gravel");

    tileid tid_ice = tiledata::gettileid("t_ice");


    for (ytile y = 0; y < chunkheight; y++)
    {
        for (htile z = -1; z < chunkwidth+1; z++)
        {
            for (htile x = -1; x < chunkwidth+1; x++)
            {
                int tile = tid_rock;

                if (y < 190) tile = 0;

                wposition w = wposition(x + cposoffset.x, y, z + cposoffset.y);

                float mheight = (randfunc::noise(w.x, w.y, w.z, 218.3f) + 1.0f) * 90.0f;

                if (y < 190)
                {
                    float factor = ((190.0f - (float)y)/190.0f) * 8.0f;
                    factor = 4.0f - factor;

                    //factor /= mheight;
                    //factor *= 2.0f;
                    //factor -= 1.0f;

                    float magnitude = (randfunc::noise(w.x+1123, w.y-1634, w.z-3452, 515.3f) + 0.7f) / 1.5f;
                    float granulation = (randfunc::noise(w.x+36123, w.y+90634, w.z+235, 430.3f) + 0.5f);

                    utils::clamp(magnitude, 0.1f, 2.0f);
                    utils::clamp(granulation, 0.0f, 1.5f);

                    float mikronoise = (randfunc::noise(w.x+5120, w.y+1643, w.z+6453, 12.7f) + 1.0f);
                    float snoise = (randfunc::noise(w.x+123, w.y+634, w.z+453, 25.3f) + 1.0f);
                    float lnoise = (randfunc::noise(w.x-7645, w.y+5634, w.z-5236, 51.0f) + 1.0f);
                    float gnoise = (randfunc::noise(w.x+7532, w.y-23511, w.z+2351, 105.0f) + 1.0f);
                    float mnoise = (randfunc::noise(w.x+1246, w.y+4724, w.z-25611, 211.0f) - 1.0f);
                    float mnoisemag = (randfunc::noise(w.x+1246, w.y+4724, w.z-25611, 471.0f) + 0.7f) / 1.5f;
                    utils::clamp(mnoisemag, 0.1f, 2.0f);

                    float holefactor = (randfunc::noise(w.x+2120, w.y+5643, w.z+1113, 221.7f)-0.6f);
                    utils::clamp(holefactor, 0.0f, 0.4f);
                    holefactor /= 0.4f;
                    float holes = (randfunc::noise(w.x-22120, w.y+32131, w.z+132, 29.7f) + 0.5f) * 4.0f;
                    utils::clamp(holes, 0.0f, 4.0f);

                    float noise = magnitude * (granulation*0.35f*mikronoise+(granulation)*0.45f* snoise + 0.65f * lnoise + 1.0f * gnoise) + mnoisemag * mnoise * 2.0f + factor;

                    noise -= holes * holefactor;

                    tile = 0;

                    if (noise > 0.8f) tile = tid_dirt;
                    if (tile == tid_dirt && magnitude > 0.7f && y < 80)
                    {
                        float spots = (randfunc::noise(w.x+4532, w.y+1234, w.z-6453, 17.0f));
                        if (spots > 0.2f)
                        {
                            tile = tid_rock;
                        }
                    }

                    chunk::biomedata biome = c.getbiome(chtilepos(x,z));

                    if (tile == tid_dirt && (y > 149 && y < 153) && biome.humidity > 50 && biome.temperature > 50)
                    {
                        tile = tid_sand;
                    }

                    if (tile == tid_dirt && y > 0)
                    {
                        if (biome.humidity < 75 && biome.temperature > 190)
                        {
                            tile = tid_sand;
                        }
                        else if (biome.temperature < 50)
                        {
                            if (biome.humidity > 70)
                            {
                                if (c.gettile(ctilepos(x,y-1,z)) == 0)
                                    tile = tid_snow;
                            }
                            else
                            {
                                float spots = (randfunc::noise(w.x+321, w.y+5324, w.z+213, 1.21f));
                                if (spots > 0.9f) tile = tid_snow;
                                else tile = tid_gravel;
                            }
                        }
                        else
                        {
                            //grassify
                            if (c.gettile(ctilepos(x,y-1,z)) == 0)
                            {
                                float spots = (randfunc::noise(w.x+7734, w.y+3231, w.z+3121, 1.3f));
                                if (spots < 0.0f) tile = tid_grass;
                                else tile = tid_grass2;
                            }
                        }
                    }

                    if (y < 190 && y > 150 && tile == 0)
                    {
                        if (biome.temperature < 50 && c.gettile(ctilepos(x,y-1,z)) == 0)
                        {
                            tile = tid_ice;
                        }
                        else
                        {
                            tile = 1;
                        }
                    }
                }



                //}
                c.addtile(tile);
            }
        }
    }

    //std::cout << c.tileids.size() << "wee"; //295936 korrekt

    //highest
    for (htile z = 0; z < chunkwidth; z++)
    {
        for (htile x = 0; x < chunkwidth; x++)
        {
            bool hset = false;
            for (ytile y = 0; y < chunkheight; y++)
            {
                ctilepos tpos = ctilepos(x,y,z);
                tileid tid = c.gettile(tpos);

                if (tid != 0)
                {
                    c.addhighest(y);
                    hset = true;
                    break;
                }
            }

            if (!hset)
                c.addhighest(255);
        }
    }

    for (int a = 0; a < (chunkwidth+2) * (chunkwidth+2) * chunkheight; a++)
        c.addlight();

    decorate(c);

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


    generatechunksides(c);


    threadcounter --;

    c.settag(chunk::C_GENERATED);
}

void chunkcontroller::updatesunlight(chunk& c, ctilepos ctpos, bool initial) //dette funker bare av og til
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
    }


}

void chunkcontroller::decorate(chunk& c)
{
    float numtrees = (randfunc::noise(c.cpos.x-6123, c.cpos.y+1124, 0.5f) + 1.0f)*2.0f;

    int tid_grass = tiledata::gettileid("t_grass");
    int tid_grass2 = tiledata::gettileid("t_grass2");
    int tid_sand = tiledata::gettileid("t_sand");
    int tid_snow = tiledata::gettileid("t_snow");

    for (int a = 0; a < numtrees; a++)
    {

        //trees
        float x = randfunc::noise(c.cpos.x+124, c.cpos.y-3245, 0.5f);
        float z = randfunc::noise(c.cpos.x+745, c.cpos.y+1241, 0.5f);

        x = (chunkwidth / 2) - (x * (chunkwidth / 3));
        z = (chunkwidth / 2) - (z * (chunkwidth / 3));

        ytile y = 0;

        for (y = 0; y < chunkheight; y++)
        {
            tileid tid = c.gettile(ctilepos(x,y,z));
            if (tid == tid_grass || tid == tid_grass2 || tid == tid_sand || tid == tid_snow)//gress
            {
                break;
            }
        }

        if (y < 200)
        {
            chunk::biomedata biome = c.getbiome(chtilepos(x,z));

            uint32_t voxelmodelid = 0;

            if (biome.temperature > 190 && biome.humidity < 75)
                voxelmodelid = 1;
            else if (biome.temperature > 180 && biome.humidity > 165)
                voxelmodelid = 2;
            else if (biome.humidity > 50)
                voxelmodelid = 0;

            addvoxelmodel(c, ctilepos(x,y,z), voxelmodelid, true);
        }


    }

    //grass etc
    tileid grasstile1 = tiledata::gettileid("t_grasstuft1");
    tileid grasstile2 = tiledata::gettileid("t_grasstuft2");
    tileid flower1 = tiledata::gettileid("t_flower1");
    tileid flower2 = tiledata::gettileid("t_flower2");
    tileid flower3 = tiledata::gettileid("t_flower3");
    tileid grass = tiledata::gettileid("t_grass");
    for (htile z = 0; z < chunkwidth; z++)
    {
        for (htile x = 0; x < chunkwidth; x++)
        {
            chunk::biomedata biome = c.getbiome(chtilepos(x,z));

            if (biome.temperature > 70 && biome.temperature < 160 && biome.humidity > 70)
            {
                ytile maxy = c.gethighest(chtilepos(x,z));
                if (maxy > 1 && c.gettile(ctilepos(x,maxy,z)) == grass && c.gettile(ctilepos(x,maxy-1,z)) == 0)
                {
                    int rint = utils::randint(0, 100);
                    if (rint < 20)
                        c.settile(ctilepos{x, maxy-1, z}, grasstile1);
                    if (rint > 80)
                        c.settile(ctilepos{x, maxy-1, z}, grasstile2);
                    if (rint == 44)
                        c.settile(ctilepos{x, maxy-1, z}, flower1);
                    if (rint == 45)
                        c.settile(ctilepos{x, maxy-1, z}, flower2);
                    if (rint == 46)
                        c.settile(ctilepos{x, maxy-1, z}, flower3);
                }
            }
            else
            {
                ytile maxy = c.gethighest(chtilepos(x,z));
                if (maxy > 1 && c.gettile(ctilepos(x,maxy,z)) == grass && c.gettile(ctilepos(x,maxy-1,z)) == 0)
                {
                    int rint = utils::randint(0, 100);
                    if (rint < 10)
                        c.settile(ctilepos{x, maxy-1, z}, grasstile1);
                    if (rint > 90)
                        c.settile(ctilepos{x, maxy-1, z}, grasstile2);
                }
            }
        }
    }
}

void chunkcontroller::addvoxelmodel(chunk& c, ctilepos ctpos, uint32_t voxelmodelid, bool cgenerator)
{
    voxelmodel& v = voxelmodels::getvoxelmodel(voxelmodelid);

    ctilepos offset = ctilepos(
                               ctpos.x - (v.centerbottomtile.x),
                               ctpos.y - v.centerbottomtile.y-1,
                               ctpos.z - (v.centerbottomtile.z)
                               );

    for (voxelmodel::point& vp : v.points)
    {
        ctilepos cpos = ctilepos(offset.x + vp.tilepos.x, offset.y + vp.tilepos.y, offset.z + vp.tilepos.z);
        if (chunkcoords::withinextendedchunkbounds(cpos))
        {
            tileid t = c.gettile(cpos);
            if (t == 0)
            {
                c.settile(cpos, vp.tid);
            }
        }
    }
}


void chunkcontroller::generatechunksides(chunk& c)
{
    int tile = 0;
    int neighbour = 0;

    for (int y = 0; y < chunkwidth*chunkwidth*chunkheight; y++)
    {
        c.addside();
    }

    for (int y = 0; y < chunkheight; y++)
    {
        for (int z = 0; z < chunkwidth; z++)
        {
            for (int x = 0; x < chunkwidth; x++)
            {
                ctilepos tilepos = ctilepos{x,y,z};
                tile = c.gettile(tilepos);
                if (!tiledata::isempty(tile))
                {
                    neighbour = c.gettile(ctilepos{x-1,y,z});
                    if (tiledata::renderside(tile, neighbour, 0)) c.addside(tilepos, tiledata::SIDE_XM);

                    neighbour = c.gettile(ctilepos{x+1,y,z});
                    if (tiledata::renderside(tile, neighbour, 1)) c.addside(tilepos, tiledata::SIDE_XP);

                    if (y > 0)
                    {
                        neighbour = c.gettile(ctilepos{x,y-1,z});
                        if (tiledata::renderside(tile, neighbour,2)) c.addside(tilepos, tiledata::SIDE_YM);
                    }
                    if (y < chunkheight-1)
                    {
                        neighbour = c.gettile(ctilepos{x,y+1,z});
                        if (tiledata::renderside(tile, neighbour,3)) c.addside(tilepos, tiledata::SIDE_YP);
                    }

                    neighbour = c.gettile(ctilepos{x,y,z-1});
                    if (tiledata::renderside(tile, neighbour, 4)) c.addside(tilepos, tiledata::SIDE_ZM);

                    neighbour = c.gettile(ctilepos{x,y,z+1});
                    if (tiledata::renderside(tile, neighbour,5)) c.addside(tilepos, tiledata::SIDE_ZP);

                }
            }
        }
    }
}
