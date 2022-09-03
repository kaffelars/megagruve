#include "consts.h"
#include "chunktilemanager.h"
#include "chunkcontroller.h"

#include "chunkcoords.h"
#include "chunkwatermanager.h"
#include "chunklight.h"

#include "map_obj_manager.h"
#include "map_obj.h"

#include "tiledata.h"
#include "particlemanager.h"

#include "maincharcontroller.h"

namespace chunktilemanager
{
    struct cchangetile
    {
        chunkpos cpos;
        ctilepos ctpos;
        tileid tid;
        uint8_t extrainfo; //f.eks. mapobj id
        breakageinfo breakage;
        //uint8_t forwardside {0};
    };

    std::vector<cchangetile> ctilestochange;
    std::vector<cchangetile> ctilestochangequeue;
}

void chunktilemanager::cleartilestochange()
{
    ctilestochange.clear();
    ctilestochangequeue.clear();
}

void chunktilemanager::addtiletochange(wtilepos wtile, tileid newtileid, uint8_t extrainfo, breakageinfo breakage)
{
    chunkpos cpos = chunkcoords::wpostocpos(wtile);
    ctilepos ctpos = chunkcoords::wtilepostoctilepos(wtile);
    addctiletochange(cpos, ctpos, newtileid, extrainfo, breakage);
}

void chunktilemanager::addctiletochange(chunkpos cpos, ctilepos ctpos, tileid newtileid, uint8_t extrainfo, breakageinfo breakage)
{
    ctilestochangequeue.emplace_back(cchangetile{cpos, ctpos, newtileid, extrainfo, breakage});
}

bool chunktilemanager::checkoutsidetiles(chunk& c) //updates tiles in neighbouring chunks, e.g. from trees over border etc.
{
    if (c.anyoutsidetiles)
    {
        int numempty = 0;
        breakageinfo b {false};

        for (int y = -1; y <= 1; y++)
        {
            for (int x = -1; x <= 1; x++)
            {
                if (!(x == 0 && y == 0))
                {
                    int index = (x+1) + (y+1)*3;
                    if (!c.outsidetiles[index].empty())
                    {
                        chunkpos cp = c.cpos + chunkpos{x,y};
                        if (chunkcontroller::chunkexists(cp))
                        {
                            if (chunkcontroller::getchunk(cp).gettag() == chunk::C_READY)
                            {
                                for (glm::ivec4& v : c.outsidetiles[index])
                                {
                                    if (!changectile(cp, ctilepos{v.x, v.y, v.z}, v.a, 0, b, 0, false))
                                    {
                                        //?
                                    }
                                }

                                c.outsidetiles[index].clear();
                                numempty++;
                            }
                        }
                    }
                    else
                    {
                        numempty++;
                    }
                }
            }
        }

        if (numempty == 8)
        {
            c.anyoutsidetiles = false;
        }
    }

    return true;
}

void chunktilemanager::removemapobj(chunk& c, ctilepos ctpos)
{
    c.removechunkobj(ctpos);
}

void chunktilemanager::interactobjaround(chunkpos cpos, ctilepos ctpos, ctilepos effectoffset, mainchar& mchar)
{
    for (int a = 0; a < 6; a++)
    {
        wtilepos nwtpos = ctpos + sideoffsets[a] + effectoffset;
        nwtpos.x += cpos.x * chunkwidth;
        nwtpos.z += cpos.y * chunkwidth;

        chunkpos ncpos = chunkcoords::wpostocpos(nwtpos);
        ctilepos nctpos = chunkcoords::wtilepostoctilepos(nwtpos);

        chunk& c = chunkcontroller::getchunk(ncpos);

        if (c.gettag() == chunk::C_READY)
        {
            if (c.gettile(nctpos) == 255)
            {
                std::shared_ptr<map_obj>& m = c.getmapobj(nctpos);
                if (m->isindirectlyinteractable())
                    m->interact(mchar);
            }
        }
    }

}

/*std::shared_ptr<map_obj>& chunktilemanager::getmapobj(wtilepos wtpos) //trengs ikke?
{
    chunkpos cpos = chunkcoords::wpostocpos(wtpos);
    ctilepos ctpos = chunkcoords::wtilepostoctilepos(wtpos);

    chunk& c = chunkcontroller::getchunk(cpos);

    if (c.gettag() == chunk::C_READY)
    {
        if (c.gettile(ctpos) == 255)
        {
            return c.getmapobj(ctpos);
        }
    }

    return shared_ptr<map_obj>(nullptr);
}*/

void chunktilemanager::changetiles()
{
    for (cchangetile& c: ctilestochangequeue)
    {
        ctilestochange.push_back(c);
    }
    ctilestochangequeue.clear();


    if (ctilestochange.empty()) return;

    auto vit = ctilestochange.begin();
    while (vit != ctilestochange.end())
    {
        if (changectile((*vit).cpos, (*vit).ctpos, (*vit).tid, (*vit).extrainfo, (*vit).breakage))
        {
            vit = ctilestochange.erase(vit);
        }
        else
        {
            ++vit;
        }
    }
}

bool chunktilemanager::changectile(wtilepos wtile, tileid newtileid, uint8_t extrainfo, breakageinfo breakage, uint8_t forwardside)
{
    chunkpos cpos = chunkcoords::wpostocpos(wtile);
    ctilepos ctpos = chunkcoords::wtilepostoctilepos(wtile);
    return changectile(cpos, ctpos, newtileid, extrainfo, breakage, forwardside);
}

bool chunktilemanager::changectile(chunkpos cpos, ctilepos ctpos, tileid newtileid, uint8_t extrainfo, breakageinfo breakage, uint8_t forwardside, bool updateneighbour)
{
    //er det et problem med map objs på border? maybe, map objs bruker coord3d - nå blir ikke map objs satt i nabochunks inntil videre, kan bli problems med lys?
    if (!chunkcontroller::chunkexists(cpos)) return false;
    chunk& c = chunkcontroller::getchunk(cpos);
    if (c.gettag() == chunk::C_READY)
    {
        tileid oldtile = c.gettile(ctpos);
        tileid oldmapobj = 0;

        if (oldtile == mapobjtileid)
        {
            oldmapobj = c.getmapobj(ctpos)->mapobjid;
            removemapobj(c, ctpos); //
        }

        c.settile(ctpos, newtileid);

        if (newtileid == mapobjtileid) //obj
        {
            //hmmmm

            if (chunkcoords::withinextendedchunkbounds(ctpos))
            {
                chunkcontroller::addremesh(c, ctpos.y); //chunkmesher
            }

            //chunklight::updatesunlight(c, ctpos, false);

            mapobjplacement placement = map_obj_manager::getmapobjinfo(extrainfo).placement;

            switch (placement)
            {
            case mapobjplacement::ground:
                {
                    c.addchunkobj(ctpos, extrainfo, getforwardside(cpos, ctpos));
                    break;
                }
            case mapobjplacement::surface:
                {
                    c.addchunkobj(ctpos, extrainfo, forwardside);
                    break;
                }
            case mapobjplacement::verticalsurface:
                {
                    if (forwardside != 2 && forwardside != 3)
                        c.addchunkobj(ctpos, extrainfo, forwardside);
                    break;
                }
            case mapobjplacement::horizontalsurface:
                {
                    if (forwardside == 2 && forwardside == 3)
                        c.addchunkobj(ctpos, extrainfo, forwardside);
                    break;
                }
            }



            return true;
        }
        else
        {
            if (oldtile == newtileid) return true; //ingenting å endre

            if (newtileid == 1)// && chunkcoords::withinchunkbounds(ctpos)) //water
            {
                chunkwatermanager::addactivewatertile(cpos, ctpos);
                //std::cout << "hey";
            }

            if (chunkcoords::withinextendedchunkbounds(ctpos))
            {
                c.setremeshy(ctpos.y);
                if (ctpos.y > 1) c.setremeshy(ctpos.y-1);
                if (ctpos.y < chunkheight-2) c.setremeshy(ctpos.y+1);
            }

            if (tiledata::gettiletype(oldtile) != tiledata::gettiletype(newtileid)) //check if sunupdates = necessary
            {
                chunklight::updatesunlight(c, ctpos, false);
            }

            if (updateneighbour && chunkcoords::withinchunkbounds(ctpos))
            {
                breakageinfo b;
                if (ctpos.x == 0) addctiletochange(chunkpos{cpos.x-1, cpos.y}, ctilepos{chunkwidth, ctpos.y, ctpos.z}, newtileid, extrainfo, b);
                if (ctpos.x == chunkwidth-1) addctiletochange(chunkpos{cpos.x+1, cpos.y}, ctilepos{-1, ctpos.y, ctpos.z}, newtileid, extrainfo, b);
                if (ctpos.z == 0) addctiletochange(chunkpos{cpos.x, cpos.y-1}, ctilepos{ctpos.x, ctpos.y, chunkwidth}, newtileid, extrainfo, b);
                if (ctpos.z == chunkwidth-1) addctiletochange(chunkpos{cpos.x, cpos.y+1}, ctilepos{ctpos.x, ctpos.y, -1}, newtileid, extrainfo, b);
            }

            if (breakage.breakage)
            {
                uint8_t textureid;
                uint8_t glow;
                if (oldtile == 255)
                {
                    textureid = map_obj_manager::getmapobjinfo(oldmapobj).breaktextureid;
                    glow = map_obj_manager::getmapobjinfo(oldmapobj).glow;
                }
                else
                {
                    textureid = tiledata::gettileinfo(oldtile).breaktextureid;
                    glow = tiledata::gettileinfo(oldtile).glow;
                }
                wposition tilepos = wposition(cpos.x * chunkwidth + ctpos.x, ctpos.y, cpos.y * chunkwidth + ctpos.z);

                for (int a =0 ; a < breakage.particlenum; a++)
                {
                    //direction chardir = (-maincharcontroller::getviewdir() / 10.0f);
                    float randx = utils::randint(-3, 3);
                    float randz = utils::randint(-3, 3);
                    randx /= 30.0f;
                    randz /= 30.0f;
                    int duration = 2000 + utils::randint(-500, 500);
                    particlemanager::addparticle(wposition(tilepos.x + 0.5f, tilepos.y + 0.5f, tilepos.z + 0.5f), breakage.particlevel + velocity(randx, -0.1f, randz), textureid, 15, duration, glow, 1.0f, false);
                }

                //water
                if (chunkcoords::withinchunkbounds(ctpos))
                {
                    for (int a = 0; a < 6; a++)
                    {
                        if (c.gettile(ctpos + sideoffsets[a]) == 1)
                        {
                            chunkwatermanager::addactivewatertile(cpos, ctpos + sideoffsets[a]);
                        }
                    }
                }
            }

            return true;
        }
    }
    else
    {
        return false;
    }
}

void chunktilemanager::explodetiles(wtilepos wtile, int32_t explosionpower)
{
    for (int x = -explosionpower; x <= explosionpower; x++)
    {
        for (int z = -explosionpower; z <= explosionpower; z++)
        {
            for (int y = -explosionpower; y <= explosionpower; y++)
            {
                if (glm::distance(glm::vec3(0.0f), glm::vec3(x,y,z)) <= explosionpower && wtile.y + y > 0 && wtile.y + y < chunkheight)
                {
                    tileid tid = chunkcontroller::gettileid(wtile + wtilepos{x,y,z});
                    if (!tiledata::needssupport(tid) && tiledata::gettileinfo(tid).hardness != 255)
                    {
                        velocity partvel = velocity{x,y,z};
                        partvel /= 10.0f;
                        breakageinfo b {true, partvel, 2};
                        breaktilewithinfo(wtile + wtilepos{x,y,z}, b);
                    }
                }
            }
        }
    }
}

void chunktilemanager::breaktilewithinfo(wtilepos wtile, breakageinfo b)
{
    tileid tid = chunkcontroller::gettileid(wtile);
    if (tid > 1) //air and water cannot be broken normally
    {
        addtiletochange(wtile, 0, 0, b);

        if (wtile.y > 0)
        {
            wtile.y--;
            tileid tid = chunkcontroller::gettileid(wtile);
            if (tiledata::needssupport(tid))
            {
                breaktile(wtile);
            }
        }
    }
}


void chunktilemanager::breaktile(wtilepos wtile)
{
    //drop stuff?
    chunktilemanager::breakageinfo b {true};
    breaktilewithinfo(wtile, b);
}

uint8_t chunktilemanager::getforwardside(chunkpos cpos, ctilepos ctpos)
{
    return getforwardside(wtilepos{cpos.x * chunkwidth + ctpos.x, ctpos.y, cpos.y * chunkwidth + ctpos.z});
}

uint8_t chunktilemanager::getforwardside(wtilepos wtpos)
{
    uint8_t forwardside = 0;
    wtpos += wtilepos{0.5f, 0.5f, 0.5f}; //center av tile

    glm::vec3 viewdir = point{wtpos} - maincharcontroller::getmaincharcamera();
    viewdir.y = 0.0f;
    viewdir = -glm::normalize(viewdir);

    for (int a = 0; a < 6; a++)
    {
        if (a != 2 && a!=3)
        {
            glm::vec3 sf = sideoffsets[a];
            if (glm::dot(viewdir, sf) > 0.707f) return a; //innenfor 45 grader
        }
    }

    return forwardside;
}
