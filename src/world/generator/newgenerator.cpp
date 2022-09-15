#include "consts.h"
#include "newgenerator.h"
#include "randfunc.h"
#include "chunkdecorator.h"

#include "coarsearray.h"
#include "twoarray.h"
#include "chunkcoords.h"

newgenerator::newgenerator()
{
    //ctor
}

newgenerator::~newgenerator()
{
    //dtor
}

void newgenerator::generator(chunk& c)
{
    chunkpos cposoffset = c.cpos;
    cposoffset.x *= chunkwidth;
    cposoffset.y *= chunkwidth;

    generatebiomes(c, cposoffset);

    //land
    std::vector<float> land;
    generateroughland(land, cposoffset);
    generateworld(c, land, cposoffset);
}

void newgenerator::generateworld(chunk& c, std::vector<float>& land, chunkpos cposoffset)
{
    tileid tid_grass = tiledata::gettileid("t_grass");
    tileid tid_grass2 = tiledata::gettileid("t_grass2");

    tileid tid_dirt = tiledata::gettileid("t_dirt");

    tileid tid_sand = tiledata::gettileid("t_sand");
    tileid tid_lava = tiledata::gettileid("t_lava");
    tileid tid_rock = tiledata::gettileid("t_rock");
    tileid tid_clay = tiledata::gettileid("t_clay");

    tileid tid_snow = tiledata::gettileid("t_snow");
    tileid tid_gravel = tiledata::gettileid("t_gravel");

    tileid tid_ice = tiledata::gettileid("t_ice");

    tileid tid_coalore = tiledata::gettileid("t_coalore");
    tileid tid_ironore = tiledata::gettileid("t_ironore");
    tileid tid_diamondore = tiledata::gettileid("t_diamondore");

    tileid tid_bedrock = tiledata::gettileid("t_bedrock");

    tileid tid_mossydirt = tiledata::gettileid("t_mossydirt");

    int rx, ry, rz;

    /*int coarsewid = ((chunkwidth + 2) / 3) + 1;

    coarsearray<float> oceans(coarsewid);*/

    twoarray<float, chunkwidth+2> landheight;
    twoarray<float, chunkwidth+2> beaches;
    twoarray<float, chunkwidth+2> mountains;
    twoarray<float, chunkwidth+2> mountainsteep;
    twoarray<float, chunkwidth+2> terrain;
    twoarray<float, chunkwidth+2> topsoil;
    twoarray<float, chunkwidth+2> avgheight;
    twoarray<float, chunkwidth+2> rivers;
    twoarray<float, chunkwidth+2> riversize;
    twoarray<float, chunkwidth+2> highlands;
    twoarray<float, chunkwidth+2> smallspots;
    twoarray<float, chunkwidth+2> noise;

    //coarsearray<float, chunkwidth+2> test;

    for (htile z = -1; z < chunkwidth+1; z++)
    {
        rz = z + cposoffset.y;
        for (htile x = -1; x < chunkwidth+1; x++)
        {
            rx = x + cposoffset.x;
            landheight.setdata(x+1,z+1, randfunc::terrain(0.5f, 0.5f, 711.1f, 1.0f, rx, 0, rz, 6));
            terrain.setdata(x+1,z+1, randfunc::terrain(0.5f, 0.5f, 231.0f, 1.0f, rx, 0, rz, 6));
            highlands.setdata(x+1,z+1, randfunc::noise(rx, rz, 1137.2f));
            beaches.setdata(x+1, z+1, randfunc::noise(rx, rz, 337.2f));
            mountains.setdata(x+1, z+1, pow(randfunc::noise(rx, rz, 491.5f), 2.0f));
            mountainsteep.setdata(x+1, z+1, randfunc::noise(rx, rz, 91.3f));
            topsoil.setdata(x+1, z+1, (randfunc::noise(rx, rz, 317.9f) + 1.0f)*3.0f + 2.0f);
            avgheight.setdata(x+1, z+1, randfunc::terrain(0.5f, 0.5f, 237.1f, 1.0f, rx, 0, rz, 3));
            rivers.setdata(x+1, z+1, randfunc::terrain(0.5f, 0.5f, 937.1f, 1.0f, rx, 0, rz, 5));
            riversize.setdata(x+1, z+1, 2.0f * (randfunc::noise(rx, rz, 631.1f)+1.0f));
            smallspots.setdata(x+1, z+1, randfunc::noise(rx, rz, 15.5f));
            noise.setdata(x+1, z+1, randfunc::noise(rx, rz, 1.1f));

            //test.setdata((x+1)/3, (z+1)/3, (randfunc::noise(rx, rz, 245.71f) + 2.0f)*120.0f);
        }
    }

    float cavernyx[9];
    float cavernx[9];
    float cavsizex[9];

    float cavernyz[9];
    float cavernz[9];
    float cavsizez[9];

    int index = 0;

    for (int z = -1; z <= 1; z++)
    {
        for (int x = -1; x <= 1; x++)
        {
            cavernx[index] = randfunc::noise(c.cpos.x+x, c.cpos.y+z, 3.3f) * 6.0f + 16.0f;
            cavernyx[index] = randfunc::noise(c.cpos.x+x, (c.cpos.y+z)* 119.5f, 5.3f) * 32.0f + 165.0f;
            cavsizex[index] = (randfunc::noise(c.cpos.x+x, (c.cpos.y+z) * 137.41f, 19.7f)) * 8.0f;

            cavernz[index] = randfunc::noise(c.cpos.x+x, c.cpos.y+z, 3.3f) * 6.0f + 16.0f;
            cavernyz[index] = randfunc::noise((c.cpos.x+x) * 76.3f, c.cpos.y+z, 5.3f) * 32.0f + 165.0f;
            cavsizez[index] = (randfunc::noise((c.cpos.x+x) * 109.3f, c.cpos.y+z, 19.7f)) * 8.0f;

            index++;
        }
    }


    for (ytile y = 0; y < chunkheight; y++) //her ville det vært lurt å ha y som inner loop, siden det er så mye som avhenger kun av x,z - men hmm...
    {
        ry = y;
        for (htile z = -1; z < chunkwidth+1; z++)
        {
            rz = z + cposoffset.y;
            for (htile x = -1; x < chunkwidth+1; x++)
            {
                rx = x + cposoffset.x;

                tileid tid = 0;

                float lh = landheight.getdata(x+1,z+1); //[(x+1) + (chunkwidth + 2) * (z+1)];
                float mt = mountains.getdata(x+1, z+1);
                float mtsteep = mountainsteep.getdata(x+1, z+1) * 2.0f;
                float bc = beaches.getdata(x+1, z+1) + 0.5f;
                float terr = terrain.getdata(x+1, z+1);
                float tps = topsoil.getdata(x+1, z+1);
                float high = highlands.getdata(x+1, z+1);
                float spotssmall = smallspots.getdata(x+1, z+1);
                float nois = noise.getdata(x+1, z+1);

                float avgh = avgheight.getdata(x+1, z+1);
                utils::clamp(avgh, 0.0f, 1.0f);

                float riv = rivers.getdata(x+1, z+1);
                float rivw = (5.0f + riversize.getdata(x+1, z+1)) / 50.0f;

                //if (riv > 0.5f - rivw && riv < 0.5 + rivw) lh = -0.1f;
                //rivers
                bool isriver = false;

                if (y < 132 && lh > -0.1f)
                {
                    float rfactor = fabs(riv - 0.5f);
                    if (rfactor < rivw)
                    {
                        //lh = 5.0f;
                        rfactor = 1.0f - (rfactor / rivw);
                        lh = lh * (1.0f - rfactor) + (-0.4f) * rfactor;
                        if (lh < -0.12f) lh = -0.12f;
                        isriver = true;
                    }
                }


                float granulation = (randfunc::noise(rx, ry, rz, 43.2f) + 1.5f) / 2.5f;

                chunk::biomedata biome = c.getbiome(ctilepos(x,y,z));

                utils::clamp(mt, 0.3f, 1.0f);
                if (mt < 0.4f)
                {
                    float factor = (mt - 0.3f) / 0.1f;
                    mt = 0.2f + 0.2f * factor;
                }
                utils::clamp(mtsteep, 0.5f, 2.0f);
                int h = 255;

                if (ry > 128) //oceans
                {
                    if (tps > 1.0f && ry == 129)
                        tid = tid_dirt;
                    else
                        tid = tid_rock;

                    if (lh < 0.0f)
                    {
                        if (ry < (128.0f - lh * 32.0f)) tid = 1; //water
                    }
                }
                else //landscape
                {
                    if (lh > 0.0f)
                    {
                        float hinc = lh * 10.0f;
                        utils::clamp(hinc, 0.0f, 1.0f);
                        h = (128.0f - mtsteep * granulation * mt * lh * 64.0f - terr * 6.0f * lh) - hinc * avgh * 14.0f;

                        if (high > 0.5f) //highlands
                        {
                            float lhf = lh * 10.0f;
                            utils::clamp(lhf, 0.0f, 1.0f);
                            h -= (high-0.5f) * 64.0f * lhf;
                        }

                        if (ry > h)
                        {
                            if (ry - h <= tps)
                                tid = tid_dirt;
                            else
                                tid = tid_rock;
                        }
                    }
                }

                if (!isriver && tid > 1 && bc > 0.0f) //beaches
                {
                    if (ry < 129+(bc * 2.0f) && ry > 129-(bc * 2.0f) && lh > -0.96f && lh < 0.04f)
                    {
                        if (biome.temperature > 48)
                            tid = tid_sand;
                        else
                            tid = tid_snow;
                    }
                }

                if (isriver) //river side clay deposits
                {
                    if (tid > 1 && (ry == 129 || ry == 130 || ry == 131) && spotssmall > 0.5f)
                        tid = tid_clay;
                }

                if (tid == tid_dirt && biome.humidity < 59) //dry areas dirt replacement
                {
                    if (biome.temperature > 58)
                        tid = tid_sand;
                    if (biome.temperature < 59)
                    {
                        tid = tid_gravel;
                        if (spotssmall > 0.8f) tid = tid_ice;
                    }

                }

                if (biome.humidity < 59 && biome.temperature < 59) //dirt mounds
                {
                    float mounds = (randfunc::noise(rx, ry/16, rz, 21.37f) - 0.5f) * 15.0f;
                    if (tid == 0 && ry > h - (mounds))
                    {
                        tid = tid_mossydirt;
                    }
                }

                if (y > 0 && tid == tid_dirt && c.gettile(ctilepos{x,y-1,z}) == 0) //top tile
                {
                    if (biome.temperature > 58 && biome.humidity > 58)
                    {
                        if (nois < 0.0f) tid = tid_grass2;
                        else tid = tid_grass;
                    }

                    if (biome.temperature < 59 && biome.humidity > 58)
                        tid = tid_snow;
                }

                if (tid > 1 && biome.temperature < 29 && biome.humidity > 170 && y < 100)
                {
                    if (spotssmall < -0.5) tid = tid_ice;
                }

                if (y > 0 && tid == 1 && biome.temperature < 59 && c.gettile(ctilepos{x,y-1,z}) == 0) //is på kaldt vann
                {
                    tid = tid_ice;
                }

                if (y > 0 && tid == tid_rock && c.gettile(ctilepos{x,y-1,z}) == 1)
                {
                    tid = tid_sand;
                }

                /*if (x > 14 && x < 18 && z > 14 && z < 18 && y == int(64 + (caverny[(x-15) + (z-15)*3]-192.0f) / 4.0f))
                {
                    tid = tid_snow;
                }*/

                //test
                /*if (y > test.getaverageddata(x,z))
                    tid = 2;
                else
                    tid = 0;*/

                //caverns?
                //glm::vec2 centercav = glm::vec2(16, caverny[4]);
                float cyx = 0.0f;
                float cyz = 0.0f;
                float cx = 0.0f;
                float cz = 0.0f;
                float csizx = 3.0f;
                float csizz = 3.0f;
                float factor = 0.0f;
                float caveblobs = (randfunc::noise(rx, ry, rz, 13.7f)) * 3.0f;
                if (x < 16)
                {
                    factor = ((float(x) + 16.0f) / 32.0f);
                    cyx = cavernyx[3] + (cavernyx[4] - cavernyx[3])*factor;
                    cx = cavernx[3] + (cavernx[4] - cavernx[3])*factor;
                    csizx = cavsizex[3] + (cavsizex[4] - cavsizex[3])*factor;
                    float offset = abs(cyx - y);
                    csizx = csizx - offset + caveblobs;
                }
                else
                {
                    factor = ((float(x) - 16.0f) / 32.0f);
                    cyx = cavernyx[4] + (cavernyx[5] - cavernyx[4])*factor;
                    cx = cavernx[4] + (cavernx[5] - cavernx[4])*factor;
                    csizx = cavsizex[4] + (cavsizex[5] - cavsizex[4])*factor;
                    float offset = abs(cyx - y);
                    csizx = csizx - offset + caveblobs;
                }

                if (z < 16)
                {
                    factor = ((float(z) + 16.0f) / 32.0f);
                    cyz = cavernyz[1] + (cavernyz[4] - cavernyz[1])*factor;
                    cz = cavernz[1] + (cavernz[4] - cavernz[1])*factor;
                    csizz = cavsizez[1] + (cavsizez[4] - cavsizez[1])*factor;
                    float offset = abs(cyz - y);
                    csizz = csizz - offset + caveblobs;
                }
                else
                {
                    factor = ((float(z) - 16.0f) / 32.0f);
                    cyz = cavernyz[4] + (cavernyz[7] - cavernyz[4])*factor;
                    cz = cavernz[4] + (cavernz[7] - cavernz[4])*factor;
                    csizz = cavsizez[4] + (cavsizez[7] - cavsizez[4])*factor;
                    float offset = abs(cyz - y);
                    csizz = csizz - offset + caveblobs;
                }



                //csiz *= (spotssmall + 1.0f) * 2.0f;
                if (z > cx- csizx && z < cx+ csizx && y > cyx - csizx*1.3f && y < cyx + csizx*1.3f)
                {
                    if (csizx > 2 && y > (128.0f - lh * 32.0f)+csizx + 2)
                        tid = 0;
                }
                else if (x > cz- csizz && x < cz+ csizz && y > cyz - csizz*1.3f && y < cyz + csizz*1.3f)
                {
                    if (csizz > 2 && y > (128.0f - lh * 32.0f)+csizz + 2)
                        tid = 0;
                }

                //more caverns
                float cavos = (randfunc::noise(rx+321, ry*2, rz-311, 121.37f) + 1.0f)/4.0f;
                cavos += (randfunc::noise(rx+655, ry-312, rz+611, 33.19f) + 1.0f)/4.0f;
                if (tid > 1 && ry > 150 && cavos > 1.3f - lh)
                    tid = 0;


                if (tid == tid_rock) //ore veins
                {
                    float coalore = randfunc::noise(rx-523, ry + 123, rz-21, 17.3f);
                    if (coalore > 0.9f || coalore < -0.9f) tid = tid_coalore;
                    if (y > 128)
                    {
                        float ironore = randfunc::noise(rx-5321, ry + 1451, rz-3429, 23.7f);
                        if (ironore > 0.92f) tid = tid_ironore;
                    }
                    if (y > 180)
                    {
                        float diamondore = randfunc::noise(rx+1323, ry - 1451, rz+321, 27.3f);
                        if (diamondore > 0.94f) tid = tid_diamondore;
                    }
                }


                if (y == 255) tid = tid_bedrock; //bedrock at complete bottom of world

                if (tid == 0 && y > 230) tid = tid_lava; //lava at bottom of world

                c.settile(ctilepos{x,y,z}, tid);
            }
        }
    }

    //carve caverns
    /*for (int z = -1; z < chunkwidth+2; z++)
    {
        float distx = (float)(z+1) / (float)(chunkwidth + 1);
        int curcavernx = cavernx[0] + (cavernx[2] - cavernx[0]) * distx;
        int curcavernxy = (cavernx[1] + (cavernx[3] - cavernx[1]) * distx);
        int curcavernxsize = cavernsizex[0] + (cavernsizex[1] - cavernsizex[0]) * distx;

        for (int y = curcavernxy - curcavernxsize; y < curcavernxy + curcavernxsize; y++)
        {
            for (int x = curcavernx - curcavernxsize; x < curcavernxy + curcavernxsize; x++)
            {
                c.settile(ctilepos{x,y,z}, 0);
            }
        }
    }*/
}

void newgenerator::printgenvalues(chunk& c)
{
    chunkpos cposoffset = c.cpos;
    cposoffset.x *= chunkwidth;
    cposoffset.y *= chunkwidth;

    //biome.humidity < 59 && biome.temperature < 59 mounds

    int x = 16;
    int z = 16;

    int rz = z + cposoffset.y;
    int rx = x + cposoffset.x;
    int ry = 123;

    float tempnoise = randfunc::terrain(0.5f, 0.5f, 1671.1f, 1.0f, rx + 8192.3f, 0, rz-398.0f, 7) * 175.0f;
    float humidnoise = randfunc::terrain(0.5f, 0.5f, 1819.3f, 1.0f, rx - 3133.3f, 0, rz+2911.4f, 7) * 175.0f;

    utils::clamp(tempnoise, -127.0f, 128.0f);
    utils::clamp(humidnoise, -127.0f, 128.0f);

    std::cout << "-------\nchunk: " << c.cpos.x << " - " << c.cpos.y << "\n";
    std::cout << "temp " << tempnoise + 127 << "\n";
    std::cout << "humid " << humidnoise + 127 << "\n";
    std::cout << "landheight " << randfunc::terrain(0.5f, 0.5f, 711.1f, 1.0f, rx, 0, rz, 6) << "\n";
    std::cout << "terrain " <<  randfunc::terrain(0.5f, 0.5f, 231.0f, 1.0f, rx, 0, rz, 6) << "\n"; //<0
    std::cout << "highlands " <<  randfunc::noise(rx, rz, 1137.2f) << "\n";
    std::cout << "beaches " <<  randfunc::noise(rx, rz, 337.2f) << "\n";
    std::cout << "mountains " <<  randfunc::noise(rx, rz, 491.5f) << "\n"; //<0
    std::cout << "mountainsteep " <<  randfunc::noise(rx, rz, 91.3f) << "\n";
    std::cout << "topsoil " <<  randfunc::noise(rx, rz, 317.9f) << "\n";
    std::cout << "avgheight " <<  randfunc::terrain(0.5f, 0.5f, 237.1f, 1.0f, rx, 0, rz, 3) << "\n";
    std::cout << "rivers " <<  randfunc::terrain(0.5f, 0.5f, 937.1f, 1.0f, rx, 0, rz, 5) << "\n";
    std::cout << "riversize " <<  randfunc::noise(rx, rz, 631.1f) << "\n";
    std::cout << "smallspots " <<  randfunc::noise(rx, rz, 15.5f) << "\n";
    std::cout << "noise " <<  randfunc::noise(rx, rz, 1.1f) << "\n"; //<0
    std::cout << "granulation " << randfunc::noise(rx, ry, rz, 43.2f) << "\n";

    int ory = ry * 3;
    int orx = x * 3 + cposoffset.x - 1;
    int orz = z * 3 + cposoffset.y - 1;

    std::cout << "oceans: " << randfunc::noise(orx, ory, orz, 732.3f) << "\n"; //<0
}


bool newgenerator::isacceptableforvillage(chunkpos cpos)
{
    if (std::abs(cpos.x) > 5 && std::abs(cpos.y) > 5)
    {
        float villagos = randfunc::noise(cpos.x-391, cpos.y+333, 32.5f);

        if (villagos > 0.6f)
        {
            chunkpos cposoffset = cpos;
            cposoffset.x *= chunkwidth;
            cposoffset.y *= chunkwidth;

            int x = 16;
            int z = 16;
            int y = 123;

            int rx = x + cposoffset.x;
            int rz = z + cposoffset.y;

            float tempnoise = randfunc::terrain(0.5f, 0.5f, 1671.1f, 1.0f, rx + 8192.3f, 0, rz-398.0f, 7) * 175.0f;
            float humidnoise = randfunc::terrain(0.5f, 0.5f, 1819.3f, 1.0f, rx - 3133.3f, 0, rz+2911.4f, 7) * 175.0f;

            utils::clamp(tempnoise, -127.0f, 128.0f);
            utils::clamp(humidnoise, -127.0f, 128.0f);

            if (tempnoise + 127 > 66 && humidnoise + 127 > 66)
            {
                float mountains = randfunc::noise(rx, rz, 491.5f);
                float terrain =  randfunc::terrain(0.5f, 0.5f, 231.0f, 1.0f, rx, 0, rz, 6);
                float landheight = randfunc::terrain(0.5f, 0.5f, 711.1f, 1.0f, rx, 0, rz, 6);

                if (terrain < 0.0f && mountains < 0.0f && landheight > 0.0f && landheight < 0.35f)// && oceans < -0.1f)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}


float newgenerator::getlandweight(std::vector<float>& land, ctilepos ctpos)
{
    ctpos.y -= 1;

    int8_t cmin[3] = {0,0,0};
    int8_t cmax[3] = {0,0,0};
    float fcent[3] = {(float)ctpos.x, (float)ctpos.y, (float)ctpos.z};
    int cent[3] = {0,0,0};

    int hwid = ((chunkwidth + 2) / 3) + 1;

    for (int a = 0; a < 3; a++)
    {
        cent[a] = ceil(fcent[a] / 3.0f);
        if (ctpos[a] % 3 == 0) cmax[a] = 1;
        if (ctpos[a] - 1 % 3 == 0) cmin[a] = 1;
    }

    float numbos = 0.0f;
    float terrain = 0.0f;

    for (int y = - cmin[1]; y <= cmax[1]; y++)
    {
        for (int z = -cmin[2] ; z<= cmax[2]; z++)
        {
            for (int x = -cmin[0] ; x<= cmax[0]; x++)
            {
                terrain += land[(x + cent[0]) + hwid*((z + cent[2]) + (y + cent[1])*hwid)];
                numbos ++;
            }
        }
    }

    terrain /= numbos; //numbos kan ikke bli 0

    //float terrain = randfunc::noise(ctpos.x, ctpos.y, ctpos.z, 33.3f);

    return terrain;
}

void newgenerator::generateroughland(std::vector<float>& land, chunkpos cposoffset)
{
    int hwid = ((chunkwidth + 2) / 3) + 1;
    int hheight = (chunkheight / 3) + 1;

    for (int y = 0; y < hheight; y++)
    {
        for (int z =0 ; z< hwid; z++)
        {
            for (int x =0 ; x< hwid; x++)
            {
                int ry = y * 3;
                int rx = x * 3 + cposoffset.x - 1;
                int rz = z * 3 + cposoffset.y - 1;

                float terrain = 0.0f;
                float oceans = randfunc::noise(rx, ry, rz, 732.3f);

                if (ry > 128)
                {
                    terrain = 1.0f;
                    if (oceans > 0.0f)
                    {
                        if (ry < 128.0f + (oceans * 64.0f)) terrain = 0.0f;
                    }
                }
                /*else
                {
                    terrain = randfunc::noise(rx, ry, rz, 33.3f);
                    float prembo = 128 - ry;
                    prembo /= 128.0f;
                    terrain -= prembo;
                }*/

                land.push_back(terrain);
            }
        }
    }
}

void newgenerator::generatebiomes(chunk& c, chunkpos cposoffset)
{
    for (htile z = -1; z < chunkwidth+1; z++)
    {
        for (htile x = -1; x < chunkwidth+1; x++)
        {
            uint8_t temp = 127;
            uint8_t humid = 127;

            int rx = x + cposoffset.x;
            int rz = z + cposoffset.y;

            //float tempnoise = (randfunc::noise(rx +123, -321, rz-3452, 793.3f)) * 175.0f;
            //float humidnoise = (randfunc::noise(rx +564, 221, rz+391, 813.3f)) * 175.0f;

            float tempnoise = randfunc::terrain(0.5f, 0.5f, 1671.1f, 1.0f, rx + 8192.3f, 0, rz-398.0f, 7) * 175.0f;
            float humidnoise = randfunc::terrain(0.5f, 0.5f, 1819.3f, 1.0f, rx - 3133.3f, 0, rz+2911.4f, 7) * 175.0f;

            utils::clamp(tempnoise, -127.0f, 128.0f);
            utils::clamp(humidnoise, -127.0f, 128.0f);

            temp += tempnoise;
            humid += humidnoise;

            c.setbiome(chunk::biomedata{temp, humid}, chtilepos{x,z});
        }
    }
}

newgenerator::tileh newgenerator::gettileheight(chunk& c, htile x, htile z)
{
    tileid tid;

    for (ytile y = 0; y < chunkheight; y++)
    {
        tid = c.gettile(ctilepos(x,y,z));
        if (tid != 0)
        {
            return tileh{.y = y, .tid = tid};
        }
    }
    return tileh{.y = 255, .tid = 0};
}


void newgenerator::decorate(chunk& c)
{
    float numtrees = (randfunc::noise(c.cpos.x-6123, c.cpos.y+1124, 37.5f) + 0.5f)*15.0f;

    if (numtrees < 0.0f) numtrees = 0.0f;

    int tid_grass = tiledata::gettileid("t_grass");
    int tid_grass2 = tiledata::gettileid("t_grass2");
    int tid_sand = tiledata::gettileid("t_sand");
    int tid_snow = tiledata::gettileid("t_snow");
    int tid_stone = tiledata::gettileid("t_stone");
    int tid_planks = tiledata::gettileid("t_planks");
    int tid_water = tiledata::gettileid("t_water");

    uint32_t voaktree = chunkdecorator::getvoxelmodelid("vox_oak_tree");
    uint32_t vsprucetree = chunkdecorator::getvoxelmodelid("vox_spruce_tree");
    uint32_t voaktree2 = chunkdecorator::getvoxelmodelid("vox_oak_tree2");
    uint32_t vbirchtree = chunkdecorator::getvoxelmodelid("vox_birch_tree");
    uint32_t vtallbirchtree = chunkdecorator::getvoxelmodelid("vox_tall_birch_tree");
    uint32_t vcactus = chunkdecorator::getvoxelmodelid("vox_cactus");
    uint32_t vtalltree = chunkdecorator::getvoxelmodelid("vox_talltree");
    uint32_t vpyramid = chunkdecorator::getvoxelmodelid("vox_pyramid");

    bool village = isacceptableforvillage(c.cpos);

    chunk::biomedata cbiome = c.getbiome(ctilepos(16,128,16));
    if (!village && cbiome.humidity < 38 && cbiome.temperature > 200)
    {
        float x = randfunc::noise(c.cpos.x+124, c.cpos.y-3245, 0.5f);
        if (x > 0.96f)
        {
            tileh tileinf = gettileheight(c, 16, 16);
            if (tileinf.tid == tid_sand)
                chunkdecorator::addvoxelmodel(c, ctilepos(16,tileinf.y,16), vpyramid, true, true);
        }
    }

    std::vector<glm::ivec3> treepositions;

    if (village)
    {
        bool nbvillage[4] = {isacceptableforvillage(c.cpos + glm::ivec2(-1, 0)), isacceptableforvillage(c.cpos + glm::ivec2(1, 0)), isacceptableforvillage(c.cpos + glm::ivec2(0, -1)), isacceptableforvillage(c.cpos + glm::ivec2(0, 1))};

        int nbvillages = nbvillage[0] + nbvillage[1] + nbvillage[2] + nbvillage[3];

        std::vector<modeltoadd> modelstoadd;

        //uint32_t vhut = chunkdecorator::getvoxelmodelid("vox_hut");
        uint32_t vhutpath = chunkdecorator::getvoxelmodelid("vox_hut_path");
        uint32_t vstonehutpath = chunkdecorator::getvoxelmodelid("vox_stone_hut_path");
        //uint32_t vshut = chunkdecorator::getvoxelmodelid("vox_small_hut");
        uint32_t vshutpath = chunkdecorator::getvoxelmodelid("vox_small_hut_path");
        uint32_t vsstonehutpath = chunkdecorator::getvoxelmodelid("vox_small_stone_hut_path");
        uint32_t vflowerbed = chunkdecorator::getvoxelmodelid("vox_flowerbed");
        uint32_t vwell = chunkdecorator::getvoxelmodelid("vox_well");
        uint32_t vshed = chunkdecorator::getvoxelmodelid("vox_shed");
        uint32_t vstower = chunkdecorator::getvoxelmodelid("vox_small_tower");
        uint32_t vbtower = chunkdecorator::getvoxelmodelid("vox_big_tower");
        uint32_t vpath = chunkdecorator::getvoxelmodelid("vox_path");
        uint32_t vwpath = chunkdecorator::getvoxelmodelid("vox_wpath");

        bool activepath[4] = {nbvillage[0], nbvillage[1], nbvillage[2], nbvillage[3]};

        bool atleastonehut = false;
        bool haswell = false;
        int villagepattern = 0;
        int32_t models[4];

        if (nbvillage[0] && nbvillage[1] && nbvillage[2] && nbvillage[3])
        {
            float centos = randfunc::noise(c.cpos.x*3+131, c.cpos.y*3+139, 0.1f);
            if (centos > 0.4f) villagepattern = 1;
            else if (centos > 0.3f) villagepattern = 4;
        }

        if (nbvillages == 1)
        {
            float centos = randfunc::noise(c.cpos.x*3-141, c.cpos.y*3-39, 0.1f);
            if (centos > 0.0f) villagepattern = 2;
        }

        float stonedos = randfunc::noise(c.cpos.x+3931, c.cpos.y-991, 0.5f);

        if (villagepattern == 0)
        {
            for (int a = 0; a < 4; a++)
            {
                float randos = randfunc::noise(c.cpos.x-1123 * a, c.cpos.y+3124 * a, 0.5f);
                if (randos > 0.5f)
                {
                    if (stonedos > 0.0f)
                        models[a] = static_cast<int32_t>(vhutpath);
                    else
                        models[a] = static_cast<int32_t>(vstonehutpath);
                    atleastonehut = true;
                }
                else if (randos > -0.1f)
                {
                    if (stonedos > 0.0f)
                        models[a] = static_cast<int32_t>(vshutpath);
                    else
                        models[a] = static_cast<int32_t>(vsstonehutpath);
                    atleastonehut = true;
                }
                else if (randos > -0.3f)
                {
                    models[a] = static_cast<int32_t>(vflowerbed);
                }
                else if (randos > -0.5f && !haswell) //max 1 well
                {
                    models[a] = static_cast<int32_t>(vwell);
                    haswell = true;
                }
                else if (randos > -0.7f)
                {
                    models[a] = static_cast<int32_t>(vshed);
                }
                else if (randos > -0.8f)
                {
                    models[a] = static_cast<int32_t>(vstower);
                }
                else
                {
                    models[a] = -1;
                }
            }

            if (!atleastonehut) //makes sure there is at least one hut in the village
            {
                models[randfunc::getrandom8bitvalue(c.cpos.x, c.cpos.y) % 4] = static_cast<int32_t>(vhutpath);
            }

            for (int x = 0; x < 2; x++)
            {
                for (int z = 0; z < 2; z++)
                {
                    if (models[z + (x*2)] != -1)
                    {
                        tileh pp = gettileheight(c, 8+x*15, 8+z*15);
                        if (pp.tid != tid_water)
                        {
                            int fws[2] = {0,0};
                            if (z == 1) fws[0] = 4;
                            else fws[0] = 5;
                            if (x == 1) fws[1] = 0;
                            else fws[1] = 1;

                            float rotatox = randfunc::noise(c.cpos.x+335*x, c.cpos.y+111*z, 0.1f);

                            tileh gg = gettileheight(c, 8+x*15 + sideoffsets[fws[rotatox > 0.0f ? 0 : 1]].x * 8, 8+z*15 + sideoffsets[fws[rotatox > 0.0f ? 0 : 1]].z * 8);

                            //std::cout << rotatox << " v " << x << " - " << sideoffsets[fws[rotatox > 0.0f ? 0 : 1]].x << " -- " << z << " - " << sideoffsets[fws[rotatox > 0.0f ? 0 : 1]].z << "\n";
                            //std::cout << 8+(x*15) + (sideoffsets[fws[rotatox > 0.0f ? 0 : 1]].x * 8) << " - " << 8+(z*15) + (sideoffsets[fws[rotatox > 0.0f ? 0 : 1]].z * 8) << "\n";

                            if (std::abs(gg.y - pp.y) < 4)
                            {//stops weird stuff
                                int fwside = fws[rotatox > 0.0f ? 0 : 1];
                                //chunkdecorator::addvoxelmodel(c, ctilepos(8+x*15,gg.y+1, 8+z*15), models[z + (x*2)], true, true, fwside);
                                modelstoadd.push_back(modeltoadd{models[z + (x*2)], ctilepos(8+x*15,gg.y+1, 8+z*15), fwside});
                                if (x == 0 && (fwside == 4 || fwside == 5)) activepath[0] = true;
                                if (x == 1 && (fwside == 4 || fwside == 5)) activepath[1] = true;
                                if (z == 0 && (fwside == 0 || fwside == 1)) activepath[2] = true;
                                if (z == 1 && (fwside == 0 || fwside == 1)) activepath[3] = true;

                                //activepath[fwside < 2 ? fwside : fwside - 2] = true; //blir ikke helt riktig, fwside henger ikke sammen med path, sjekk x/z også
                            }
                        }
                    }
                    else//tree on empty spot
                    {
                        float treedos = randfunc::noise(c.cpos.x+1931*x, c.cpos.y+4991*z, 0.5f);
                        if (treedos > 0.5f)
                        {
                            treepositions.push_back(glm::ivec3(13+x*15, 13+z*15, 0));
                            treepositions.push_back(glm::ivec3(12+x*15, 6+z*15, 0));
                            treepositions.push_back(glm::ivec3(6+x*15, 10+z*15, 0));
                        }
                        else if (treedos > 0.0f)
                        {
                            treepositions.push_back(glm::ivec3(12+x*15, 9+z*15, 0));
                            treepositions.push_back(glm::ivec3(6+x*15, 5+z*15, 0));
                        }
                        else if (treedos > -0.5f)
                        {
                            treepositions.push_back(glm::ivec3(8+x*15, 8+z*15, 0));
                        }
                    }

                }
            }
        }
        else if (villagepattern == 1)
        {
            tileh gg = gettileheight(c, 16, 16);
            float rotatox = std::ceil((randfunc::noise(c.cpos.x*3+495, c.cpos.y*3+551, 0.1f) + 1.01f) * 2.5f) - 1.0f;
            modelstoadd.push_back(modeltoadd{vbtower, ctilepos(16,gg.y+1, 16), int(rotatox)});
            //chunkdecorator::addvoxelmodel(c, ctilepos(16,gg.y+1, 16), vbtower, true, true, int(rotatox));
        }
        else if (villagepattern == 2)
        {
            glm::ivec2 offset = glm::ivec2(halfchunkwidth,halfchunkwidth);
            int rotatox = 0;
            if (nbvillage[0]) {offset.x = 22;rotatox=0;}
            if (nbvillage[1]) {offset.x = 10;rotatox=1;}
            if (nbvillage[2]) {offset.y = 22;rotatox=4;}
            if (nbvillage[3]) {offset.y = 10;rotatox=5;}
            tileh gg = gettileheight(c, offset.x, offset.y);
            modelstoadd.push_back(modeltoadd{vhutpath, ctilepos(offset.x,gg.y+1, offset.y), rotatox});
        }

        bool waterends[4]; //for piers

        for (int x = 0; x < 1; x++)
        {
            tileh tt = gettileheight(c, 1 + (x * (chunkwidth-3)), chunkwidth/2);
            waterends[x] = (tt.tid == tid_water);
        }
        for (int z = 0; z < 1; z++)
        {
            tileh tt = gettileheight(c, chunkwidth/2, 1 + (z * (chunkwidth-3)));
            waterends[z + 2] = (tt.tid == tid_water);
        }

        for (int a = 0; a < 4; a++)
        {
            activepath[a] |= waterends[a];
        }

        if (villagepattern == 0 || villagepattern == 1 || villagepattern == 4)
        {
            for (int a = 1; a < chunkwidth-1; a++) //crossroads
            {
                tileh tt;
                if (!((a < 7 && !(waterends[0] || nbvillage[0])) || (a > chunkwidth - 8 && !(waterends[1] || nbvillage[1]))))
                {
                    if ((a < 16 && activepath[0]) || (a >= 16 && activepath[1]))
                    {
                        tt = gettileheight(c, a, chunkwidth/2);
                        c.trysettile(ctilepos(a, tt.y, chunkwidth/2), tt.tid == tid_water ? tid_planks : tid_stone);
                        tt = gettileheight(c, a, (chunkwidth/2)-1);
                        c.trysettile(ctilepos(a, tt.y, (chunkwidth/2)-1), tt.tid == tid_water ? tid_planks : tid_stone);
                    }

                }

                if (!((a < 7 && !(waterends[2] || nbvillage[2])) || (a > chunkwidth - 8 && !(waterends[3] || nbvillage[3]))))
                {
                    if ((a < 16 && activepath[2]) || (a >= 16 && activepath[3]))
                    {
                        tt = gettileheight(c, chunkwidth/2, a);
                        c.trysettile(ctilepos(chunkwidth/2, tt.y, a), tt.tid == tid_water ? tid_planks : tid_stone);
                        tt = gettileheight(c, (chunkwidth/2)-1, a);
                        c.trysettile(ctilepos((chunkwidth/2)-1, tt.y, a), tt.tid == tid_water ? tid_planks : tid_stone);
                    }
                }
            }
        }

        if (villagepattern == 1 || villagepattern == 4)
        {
            tileh tt = gettileheight(c, halfchunkwidth, halfchunkwidth);;
            for (int x = 7; x < 25; x++)
            {
                for (int z = 7; z < 25; z++)
                {
                    c.trysettile(ctilepos(x, tt.y, z), tt.tid == tid_water ? tid_planks : tid_stone);
                }
            }
        }

        if (villagepattern == 4) //spawn some hay blocks
        {
            tileh tt = gettileheight(c, halfchunkwidth, halfchunkwidth);
            tt.y--;

            int tid_hay = tiledata::gettileid("t_hayblock");

            for (int x = 0; x < 5; x++)
            {
                for (int z = 0; z < 5; z++)
                {
                    bool cornerx = (x == 0 || x == 4);
                    bool cornerz = (z == 0 || z == 4);

                    if (!(cornerx && cornerz))
                    {
                        c.trysettile(ctilepos(8+x, tt.y, 8+z), tid_hay);
                        c.trysettile(ctilepos(18+x, tt.y, 8+z), tid_hay);
                        //c.trysettile(ctilepos(8+x, tt.y, 18+z), tid_hay);
                        c.trysettile(ctilepos(18+x, tt.y, 18+z), tid_hay);
                    }
                }
            }

            for (int x = 0; x < 5; x++)
            {
                for (int z = 1; z < 4; z++)
                {
                    c.trysettile(ctilepos(8+x, tt.y-1, 8+z), tid_hay);
                    c.trysettile(ctilepos(18+x, tt.y-1, 8+z), tid_hay);
                    //c.trysettile(ctilepos(8+x, tt.y-1, 18+z), tid_hay);
                    c.trysettile(ctilepos(18+x, tt.y-1, 18+z), tid_hay);
                }
            }

            c.trysettile(ctilepos(10, tt.y, 19), tid_hay);
            c.trysettile(ctilepos(10, tt.y, 20), tid_hay);
            c.trysettile(ctilepos(10, tt.y, 21), tid_hay);
            c.trysettile(ctilepos(12, tt.y, 19), tid_hay);

        }

        if (villagepattern == 2)
        {
            tileh tt;
            for (int a = 1; a < halfchunkwidth; a++) //crossroads
            {
                int x = halfchunkwidth; int z = halfchunkwidth;
                if (nbvillage[0]) x = a;
                if (nbvillage[1]) x = chunkwidth -1 - a;
                if (nbvillage[2]) z = a;
                if (nbvillage[3]) z = chunkwidth - 1 - a;

                tt = gettileheight(c, x, z);
                c.trysettile(ctilepos(x, tt.y, z), tt.tid == tid_water ? tid_planks : tid_stone);
                if (x == halfchunkwidth) x--;
                else z--;
                tt = gettileheight(c, x, z);
                c.trysettile(ctilepos(x, tt.y, z), tt.tid == tid_water ? tid_planks : tid_stone);
            }
        }


        tileh tt = gettileheight(c, chunkwidth-1, chunkwidth/2-1);
        if (nbvillage[1]) chunkdecorator::addvoxelmodel(c, ctilepos(chunkwidth-1,tt.y+1, chunkwidth/2-1), (tt.tid != tid_water) ? vpath : vwpath, true, true, 0);
        tt = gettileheight(c, 0, chunkwidth/2-1);
        if (nbvillage[0]) chunkdecorator::addvoxelmodel(c, ctilepos(0,tt.y+1, chunkwidth/2-1), (tt.tid != tid_water) ? vpath : vwpath, true, true, 0);
        tt = gettileheight(c, chunkwidth/2-1, chunkwidth-1);
        if (nbvillage[3]) chunkdecorator::addvoxelmodel(c, ctilepos(chunkwidth/2-1,tt.y+1, chunkwidth-1), (tt.tid != tid_water) ? vpath : vwpath, true, true, 0);
        tt = gettileheight(c, chunkwidth/2-1, 0);
        if (nbvillage[2]) chunkdecorator::addvoxelmodel(c, ctilepos(chunkwidth/2-1,tt.y+1, 0), (tt.tid != tid_water) ? vpath : vwpath, true, true, 0);

        //add models //after road draw to avoid overdraw
        for (modeltoadd& m: modelstoadd)
        {
            chunkdecorator::addvoxelmodel(c, m.position, m.modelid, true, true, m.forwardside);
        }
    }
    else
    {
        //not village
        for (int a = 0; a < numtrees; a++) //tree positions
        {
            glm::ivec3 tp;

            float x = randfunc::noise(c.cpos.x+124+3*randfunc::getrandom8bitvalue(a*c.cpos.x, a*c.cpos.y), c.cpos.y-3245+3*randfunc::getrandom8bitvalue(a*c.cpos.y, a*c.cpos.x), 0.5f);
            float z = randfunc::noise(c.cpos.y+745+3*randfunc::getrandom8bitvalue(a*c.cpos.x, a*c.cpos.y), c.cpos.y+1241+3*randfunc::getrandom8bitvalue(a*c.cpos.y, a*c.cpos.x), 0.5f);

            //tp.x = (chunkwidth / 2) - (x * (chunkwidth / 3));
            //tp.y = (chunkwidth / 2) - (z * (chunkwidth / 3));

            tp.x = (chunkwidth / 2) - (x * (chunkwidth / 2));
            tp.y = (chunkwidth / 2) - (z * (chunkwidth / 2));

            bool toadd = true;

            if (!treepositions.empty())
            {
                for (glm::ivec3 tree : treepositions)
                {
                    if (tree.x - 1 <= tp.x && tree.x + 1 >= tp.x && tree.y - 1 <= tp.y && tree.y + 1 >= tp.y) toadd = false;
                }
            }

            if (toadd)
            {
                tp.z = (255.0f * randfunc::noise(c.cpos.y+6745+3*randfunc::getrandom8bitvalue(a*c.cpos.x, a*c.cpos.y), c.cpos.y-4643+3*randfunc::getrandom8bitvalue(a*c.cpos.y, a*c.cpos.x), 0.5f));
                treepositions.push_back(tp);
            }
        }
    }

    //for (int a = 0; a < numtrees; a++)
    //{
    for (glm::ivec3& tree : treepositions)
    {
        //trees
        float x = tree.x;
        float z = tree.y;

        ytile y = 0;
        tileid tid = 0;

        for (y = 0; y < chunkheight; y++)
        {
            tid = c.gettile(ctilepos(x,y,z));
            if (tid == tid_grass || tid == tid_grass2 || tid == tid_sand || tid == tid_snow)//gress
            {
                break;
            }
        }

        //tileid abovetid = 0;

        if (y <= 129)
        {
            int rotatos = std::round((randfunc::noise(x,z, 0.5f)+1.0f) * 2.0f);

            chunk::biomedata biome = c.getbiome(ctilepos(x,y,z));

            int32_t voxelmodelid = -1;

            if (biome.humidity < 59 && tid == tid_sand) //biome.temperature > 190 && biome.humidity < 58 && tid == tid_sand) //cactus
            {
                if (tree.z > 180)
                    voxelmodelid = vcactus;
            }
            else if (biome.temperature > 180 && biome.humidity > 165 && tid != tid_sand) //el grande tree
                voxelmodelid = vtalltree;
            else if (biome.humidity > 58 && tid != tid_sand) //trees
            {
                if (biome.temperature > 126)
                {
                    if (tree.z > 195)
                        voxelmodelid = vtallbirchtree;
                    else
                        voxelmodelid = vbirchtree;
                }
                else if (biome.temperature > 60)
                {
                    if (tree.z > 204)
                        voxelmodelid = voaktree;
                    else
                        voxelmodelid = voaktree2;
                }
                else
                {
                    if (tree.z > 125)
                        voxelmodelid = voaktree;
                    else
                        voxelmodelid = vsprucetree;
                }
            }

            if (voxelmodelid >= 0)
                chunkdecorator::addvoxelmodel(c, ctilepos(x,y,z), voxelmodelid, true, false, rotatos);
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

            if (biome.temperature > 58 && biome.temperature < 160 && biome.humidity > 58)
            {
                if (maxy > 2 && maxy < chunkheight - 3 && (ctid == grass || ctid == grass2) && c.gettile(ctilepos(x,maxy-1,z)) == 0)
                {
                    int rint = randfunc::getrandom8bitvalue(c.cpos.x * 111 + x * 13, c.cpos.y * 111 + z * 13);//utils::randint(0, 100);
                    if (rint < 50)
                        c.settile(ctilepos{x, maxy-1, z}, grasstile1);
                    if (rint > 200)
                        c.settile(ctilepos{x, maxy-1, z}, grasstile2);
                    if (rint > 60 && rint < 65)
                        c.settile(ctilepos{x, maxy-1, z}, flower1);
                    if (rint > 65 && rint < 70)
                        c.settile(ctilepos{x, maxy-1, z}, flower2);
                    if (rint > 70 && rint < 75)
                        c.settile(ctilepos{x, maxy-1, z}, flower3);

                    if (biome.humidity > 170)
                    {
                        if (rint > 75 && rint < 100)
                        {
                            c.settile(ctilepos{x, maxy-1, z}, grass_bottom);
                            c.settile(ctilepos{x, maxy-2, z}, grass_top);
                        }
                    }
                }

            }
            else
            {
                if (maxy > 2 && maxy < chunkheight-3)
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
