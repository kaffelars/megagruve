#include "consts.h"
#include "defaultgenerator.h"
#include "randfunc.h"
#include "chunkdecorator.h"

defaultgenerator::defaultgenerator()
{
    //ctor
}

defaultgenerator::~defaultgenerator()
{
    //dtor
}

void defaultgenerator::generator(chunk& c)
{
    //dimensions dims = c.cdims;
    chunkpos cposoffset = c.cpos;
    cposoffset.x *= chunkwidth;
    cposoffset.y *= chunkwidth;

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

                //float mheight = (randfunc::noise(w.x, w.y, w.z, 218.3f) + 1.0f) * 90.0f;

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

                    chunk::biomedata biome = c.getbiome(ctilepos(x,y,z));

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
                c.settile(ctilepos{x,y,z}, tile);
            }
        }
    }

    //std::cout << c.tileids.size() << "wee"; //295936 korrekt
}


void defaultgenerator::decorate(chunk& c)
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
            chunk::biomedata biome = c.getbiome(ctilepos(x,y,z));

            uint32_t voxelmodelid = 0;

            if (biome.temperature > 190 && biome.humidity < 75)
            {
                voxelmodelid = 2;
            }
            else if (biome.temperature > 180 && biome.humidity > 165)
                voxelmodelid = 3;
            else if (biome.humidity > 50)
            {
                if (biome.temperature > 126)
                    voxelmodelid = 1;
                else
                    voxelmodelid = 0;
            }

            chunkdecorator::addvoxelmodel(c, ctilepos(x,y,z), voxelmodelid, true);
        }


    }

    //grass etc
    tileid grasstile1 = tiledata::gettileid("t_grasstuft1");
    tileid grasstile2 = tiledata::gettileid("t_grasstuft2");
    tileid grass_bottom = tiledata::gettileid("t_grass_bottom");
    tileid grass_top = tiledata::gettileid("t_grass_top");
    tileid flower1 = tiledata::gettileid("t_flower1");
    tileid flower2 = tiledata::gettileid("t_flower2");
    tileid flower3 = tiledata::gettileid("t_flower3");
    tileid grass = tiledata::gettileid("t_grass");
    tileid grass2 = tiledata::gettileid("t_grass2");
    tileid snow = tiledata::gettileid("t_snow");
    for (htile z = 0; z < chunkwidth; z++)
    {
        for (htile x = 0; x < chunkwidth; x++)
        {
            ytile maxy = c.gethighest(chtilepos(x,z));
            chunk::biomedata biome = c.getbiome(ctilepos(x,maxy,z));
            tileid ctid = c.gettile(ctilepos(x,maxy,z));

            if (biome.temperature > 70 && biome.temperature < 160 && biome.humidity > 70)
            {
                if (maxy > 1 && (ctid == grass || ctid == grass2) && c.gettile(ctilepos(x,maxy-1,z)) == 0)
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

                    if (biome.humidity > 170)
                    {
                        if (rint > 30 && rint < 40)
                        {
                            c.settile(ctilepos{x, maxy-1, z}, grass_bottom);
                            c.settile(ctilepos{x, maxy-2, z}, grass_top);
                        }
                    }
                }

            }
            else
            {
                if (maxy > 1 && maxy < chunkheight-1)
                {
                    //std::cout << int(x) << " " << maxy << " " << int(z) << "\n";
                    tileid ctid = c.gettile(ctilepos(x,maxy,z));
                    if ((ctid == grass || ctid == grass2 || ctid == snow) && c.gettile(ctilepos(x,maxy-1,z)) == 0)
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
}
