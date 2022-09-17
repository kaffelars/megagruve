#include "consts.h"
#include "chunklight.h"

#include "tiledata.h"
#include "chunkcoords.h"
#include "chunklightpoints.h"

namespace chunklight
{
    struct plight
    {
        ctilepos pos;
        uint8_t light;
    };

    void initiatetilelight(chunk& c);
    void initiatesunlight(chunk& c);
}

void chunklight::generatelight(chunk& c) //initial full sunlight
{
    initiatesunlight(c);

    propagateallsunlight(c);

    initiatetilelight(c);

    propagatetilelights(c);
}

void chunklight::initiatesunlight(chunk& c)
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
            c.fillsunlayer(y/4, 15);
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
                    c.setsunlight(ctilepos(x,y,z), 15);
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

void chunklight::initiatetilelight(chunk& c)
{
    for (int yy = 0; yy < chunkheight/4; yy++)
    {
        c.filltilelightlayer(yy, 0);
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
        if (currentpos.y == chunkheight-1) break;
        tileid tid = c.gettile(currentpos);

        if (tid == 255)
        {
            sunlight -= c.getmapobj(currentpos)->lightattenuation();
        }
        else
        {
            sunlight -= tiledata::gettileinfo(tid).lightattenuation;
        }


        if (sunlight <0) sunlight=0;

        c.setsunlight(currentpos, sunlight);

        if (!initial) c.setremeshy(currentpos.y); //avoid remesh on chunk gen

        if (sunlight <= 0 && c.getsunlight(currentpos + ctilepos(0,1,0)) == 0) break;
    }
}

void chunklight::propagateallsunlight(chunk& c) //on chunk load
{
    bool propagated = true;
    bool toggle = false;
    int sl = 0;
    int sls = 0;
    uint8_t ctpsl = 0;
    tileid tid;
    ctilepos ctp;

    std::vector<plight> prop[2];

    for (int yy = 0; yy < chunkheight/4; yy++)
    {
        if (!c.sunlight.filledlayer(yy))
        {
            for (int y = yy*4; y < (yy*4)+4; y++)
            {
                for (int z = -1; z < chunkwidth+1; z++)
                {
                    for (int x = -1; x < chunkwidth+1; x++)
                    {
                        sl = c.getsunlight(ctilepos(x,y,z));
                        if (sl > 0)
                        {
                            prop[0].push_back(plight{ctilepos(x,y,z), sl});
                        }
                    }
                }
            }
        }
    }

    while (propagated)
    {

        std::vector<plight>& topropagate = prop[toggle];
        std::vector<plight>& propagateinto = prop[!toggle];

        propagateinto.clear();
        propagated = false;

        for (plight& s : topropagate)
        {
            sl = s.light - 2;
            if (sl > 0)
            {
                for (int a = 0; a < 6; a++)
                {
                    ctp = s.pos + sideoffsets[a];
                    if (chunkcoords::withinextendedchunkbounds(ctp))
                    {
                        ctpsl = c.getsunlight(ctp);
                        if (ctpsl < 15)
                        {
                            sls = sl;
                            tid = c.gettile(ctp);
                            if (tid == 255)
                            {
                                sls -= c.getmapobj(ctp)->lightattenuation();
                            }
                            else
                            {
                                sls -= tiledata::gettileinfo(tid).lightattenuation;
                            }

                            if (sls > ctpsl)
                            {
                                c.setsunlight(ctp, sls);
                                propagateinto.push_back(plight{ctp, sls});
                                propagated = true;
                            }
                        }
                    }
                }
            }
        }

        toggle = !toggle;
    }

    c.setremeshwholechunk();
}

void chunklight::propagatetilelights(chunk& c)
{
    const std::vector<chunklightpoints::lightpoint>& lightpoints = c.lightpoints.getlightpoints();

    for (const chunklightpoints::lightpoint& lpoint : lightpoints)
    {
        if (!lpoint.hasbeenpropagated)
        {
            c.settilelight(lpoint.ctpos, lpoint.light);
            propagatelight(c, lpoint.ctpos);
        }
    }

    c.lightpoints.propagated();
    c.setremeshwholechunk();
}

void chunklight::propagatelight(chunk& c, ctilepos ctpos)
{
    std::vector<plight> prop[2];
    bool propagated = true;
    bool toggle = false;
    int lgt = 0;
    int lgt2 = 0;
    ctilepos ctp;
    uint8_t ctpsl = 0;
    tileid tid = 0;

    prop[0].push_back(plight{ctpos, c.gettilelight(ctpos)});

    while (propagated)
    {
        std::vector<plight>& topropagate = prop[toggle];
        std::vector<plight>& propagateinto = prop[!toggle];

        propagateinto.clear();
        propagated = false;

        for (plight& s : topropagate)
        {
            lgt = int(s.light) - 2;
            if (lgt > 0)
            {
                for (int a = 0; a < 6; a++)
                {
                    ctp = s.pos + sideoffsets[a];
                    if (chunkcoords::withinextendedchunkbounds(ctp))
                    {
                        ctpsl = c.gettilelight(ctp);
                        if (ctpsl < 15)
                        {
                            lgt2 = lgt;
                            tid = c.gettile(ctp);
                            if (tid == 255)
                            {
                                lgt2 -= c.getmapobj(ctp)->lightattenuation();
                            }
                            else
                            {
                                lgt2 -= tiledata::gettileinfo(tid).lightattenuation;
                            }

                            if (lgt2 > ctpsl)
                            {
                                c.settilelight(ctp, lgt2);
                                propagateinto.push_back(plight{ctp, lgt2});
                                propagated = true;
                            }
                        }
                    }
                }
            }
        }

        toggle = !toggle;
    }
}
