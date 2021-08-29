#include "consts.h"
#include "chunkcontroller.h"

#include "chunkcoords.h"

#include "biomecontroller.h"
#include "particlemanager.h"
#include "chunkgenerator.h"
#include "defaultgenerator.h"
#include "chunklight.h"
#include "chunkwatermanager.h"

namespace chunkcontroller
{
    uint32_t cpostoid(chunkpos cpos);
    bool newchunk(chunkpos cpos);
    bool removechunk(chunkpos cpos);
    namespace
    {
        std::unordered_map<uint32_t, chunk> chunks;
        dimensions chunkdimensions = glm::ivec3(chunkwidth,chunkheight,chunkwidth);
    }

    std::atomic<uint32_t> threadcounter = 0;
    std::vector<chunkpos> loadedchunks; //loop heller bare gjennom elementene i unordered map
    int32_t chunksrendered = 0;



    struct cchangetile
    {
        chunkpos cpos;
        ctilepos ctpos;
        tileid tid;
        bool breakage {false};
    };

    std::vector<cchangetile> ctilestochange;
    std::vector<cchangetile> ctilestochangequeue;

    struct cdecorate
    {
        uint32_t voxelmodelid;
        chunkpos cpos;
        ctilepos ctpos;
    };

    std::vector<cdecorate> decorations;
    std::mutex decoratemutex;

    struct waterrender
    {
        chunk* c;
    };

    std::vector<waterrender> waterrenders;


    std::unique_ptr<chunkgenerator> currentchunkgenerator = std::make_unique<defaultgenerator>();
}

void chunkcontroller::adddecoration(chunkpos cpos, ctilepos ctpos, uint32_t voxelmodelid)
{
    decoratemutex.lock();
    decorations.push_back(cdecorate{voxelmodelid, cpos, ctpos});
    decoratemutex.unlock();
}

chunk& chunkcontroller::getchunk(chunkpos cpos)
{
    return chunks.at(cpostoid(cpos));
}

uint32_t chunkcontroller::cpostoid(chunkpos cpos)
{
    return ((cpos.x+500) * 1000) + (cpos.y + 500); //1000x1000, 500,500 = center
}

int32_t chunkcontroller::getchunksrendered()
{
    return chunksrendered;
}

void chunkcontroller::renderchunks(direction dir, wposition maincharposition)
{
    chunkpos centerchunk = chunkcoords::wpostocpos(maincharposition);

    waterrenders.clear();

    chunksrendered = 0;

    hdirection d = hdirection(dir.x, dir.z);

    int renderdist = settings::getisetting(settings::SET_CDIST);

    int x = 0; int y = 0;
    int dx = 0;
    int dy = -1;
    //spiral
    while (true)
    {
        if (-renderdist < x && x <= renderdist && -renderdist < y && y <= renderdist)
        {
            //std::cout << x << " " << y << "\n";
            chunkpos offset = chunkpos{x,y};
            renderchunk(centerchunk+offset);
        }
        else
        {
            break;
        }
        if (x == y || (x < 0 && x == -y) || (x > 0 && x == 1-y))
        {
            int ddx = dx;
            dx = -dy;
            dy = ddx;
        }
        x = x+dx;
        y = y+dy;
    }
}

void chunkcontroller::updatechunks()
{
    chunkwatermanager::updateactivewatertiles();

    changetiles();

    //sletter chunks out of range
    glm::vec3 charpos = maincharcontroller::getmaincharposition();
    glm::vec2 charpos2d = glm::vec2(charpos.x, charpos.z);
    int maxdist = (2+settings::getisetting(settings::SET_CDIST)) * (chunkwidth);

    for (chunkpos& c : loadedchunks)
    {
        glm::vec2 wcpos = glm::vec2(c.x * chunkwidth, c.y * chunkwidth);
        float distance = utils::getdist(charpos2d, wcpos);
        if (distance > maxdist)
        {
            //std::cout << "remove " << c.x << "-" << c.y << "\n";
            removechunk(c); //kan bare fjerne 1 chunk pr loop i denne loopen, men det er kanskje best?
            break;
        }
    }
}

int chunkcontroller::loadedchunksnum()
{
    return loadedchunks.size();
}

chunk::tlight chunkcontroller::getlight(wtilepos wtpos)
{
    chunkpos cpos = chunkcoords::wpostocpos(wtpos);
    if (chunkexists(cpos))
    {
        chunk& c = getchunk(cpos);
        chunk::ctags ctag = c.gettag();
        if (ctag == chunk::C_READY || ctag == chunk::C_REMESHING)
        {
            ctilepos ctpos = chunkcoords::wpostoctilepos(wtpos);
            return c.getalllight(ctpos);
        }
    }

    return chunk::tlight{0,0};
}

tileid chunkcontroller::gettileid(wposition wtpos)
{
    chunkpos cpos = chunkcoords::wpostocpos(wtpos);
    if (chunkexists(cpos))
    {
        chunk& c = getchunk(cpos);
        chunk::ctags ctag = c.gettag();
        if (ctag == chunk::C_READY || ctag == chunk::C_REMESHING || ctag == chunk::C_REMESHED)
        {
            ctilepos ctpos = chunkcoords::wpostoctilepos(wtpos);
            return c.gettile(ctpos);
        }
    }

    return 0;
}

tileid chunkcontroller::gettileid(wtilepos wtpos)
{
    chunkpos cpos = chunkcoords::wtilepostocpos(wtpos);
    if (chunkexists(cpos))
    {
        chunk& c = getchunk(cpos);
        chunk::ctags ctag = c.gettag();
        if (ctag == chunk::C_READY || ctag == chunk::C_REMESHING || ctag == chunk::C_REMESHED)
        {
            ctilepos ctpos = chunkcoords::wtilepostoctilepos(wtpos);
            return c.gettile(ctpos);
        }
    }

    return 0;
}

bool chunkcontroller::ischunkvisible(chunk& c) //not good when looking down
{
    wposition mcharpos = maincharcontroller::getmaincharposition();
    chunkpos curchunk = chunkcoords::wpostocpos(mcharpos);
    if (c.cpos == curchunk) return true;

    hposition cpos[4];

    cpos[0] = hposition(c.cpos.x*chunkwidth,                c.cpos.y*chunkwidth);
    cpos[1] = hposition(c.cpos.x*chunkwidth + chunkwidth,   c.cpos.y*chunkwidth);
    cpos[2] = hposition(c.cpos.x*chunkwidth,                c.cpos.y*chunkwidth + chunkwidth);
    cpos[3] = hposition(c.cpos.x*chunkwidth + chunkwidth,   c.cpos.y*chunkwidth + chunkwidth);

    hdirection mchardir = maincharcontroller::gethviewdir();

    for (int a = 0; a < 4; a++)
    {
        hdirection cdir = glm::normalize(hdirection(cpos[a].x - mcharpos.x, cpos[a].y - mcharpos.z));
        if (glm::dot(mchardir, cdir) > 0.4f) return true;
    }
    return false;
}

void chunkcontroller::renderwater()
{
    for (waterrender& w : waterrenders)
    {
        w.c->renderwater();
    }
}

void chunkcontroller::renderchunk(chunkpos cpos)
{
    if (!chunkexists(cpos))
        newchunk(cpos);

    chunk& c = getchunk(cpos);
    chunk::ctags ctag = c.gettag();

    if (threadcounter < settings::getisetting(settings::SET_MAXTHREADS) && ctag == chunk::C_READY && c.needsremesh())
    {
        threadcounter++;
        c.settag(chunk::C_REMESHING);
        ctag = chunk::C_REMESHING;
        auto t = std::thread(remeshchunk, std::ref(c));
        t.detach();
    }

    if (ctag == chunk::C_REMESHED)
    {
        c.setremeshedvbos();

        c.settag(chunk::C_READY);
        ctag = chunk::C_READY;
    }

    if (ctag == chunk::C_READY || ctag == chunk::C_REMESHING)
    {
        if (ischunkvisible(c))//simple frustum culling
        {
            chunksrendered++;
            c.render();
            waterrenders.emplace_back(waterrender{&c});
        }
    }
    else
    {
        //std::cout << chunkmeshynum << "fsef\n";
        if (threadcounter < settings::getisetting(settings::SET_MAXTHREADS))
        {
            if (ctag == chunk::C_START) //mutex
            {
                threadcounter++;
                c.settag(chunk::C_GENERATING);
                auto t = std::thread(&chunkgenerator::generatechunk, std::ref(*currentchunkgenerator), std::ref(c));
                t.detach();
                //currentchunkgenerator->generatechunk(c);
            }

            if (ctag == chunk::C_GENERATED)
            {
                threadcounter++;
                c.settag(chunk::C_MESHING);
                auto t = std::thread(meshwholechunk, std::ref(c));
                t.detach();
                //meshwholechunk(c);
            }
        }
        if (ctag == chunk::C_MESHED)
        {
            c.setallvbos();
            c.settag(chunk::C_READY);
        }
    }
}


void chunkcontroller::addtiletochange(wtilepos wtile, tileid newtileid, bool breakage)
{
    chunkpos cpos = chunkcoords::wpostocpos(wtile);
    ctilepos ctpos = chunkcoords::wtilepostoctilepos(wtile);
    addctiletochange(cpos, ctpos, newtileid, breakage);
}

void chunkcontroller::addctiletochange(chunkpos cpos, ctilepos ctpos, tileid newtileid, bool breakage)
{
    ctilestochangequeue.emplace_back(cchangetile{cpos, ctpos, newtileid, breakage});
}

void chunkcontroller::changetiles()
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
        if (changectile((*vit).cpos, (*vit).ctpos, (*vit).tid, (*vit).breakage))
        {
            vit = ctilestochange.erase(vit);
        }
        else
        {
            ++vit;
        }
    }
}

bool chunkcontroller::changectile(chunkpos cpos, ctilepos ctpos, tileid newtileid, bool breakage)
{
    if (!chunkexists(cpos)) return false;
    chunk& c = getchunk(cpos);
    if (c.gettag() == chunk::C_READY)
    {
        tileid oldtile = c.gettile(ctpos);

        if (oldtile == newtileid) return true; //ingenting å endre

        c.settile(ctpos, newtileid);

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

        if (tiledata::gettiletype(oldtile) != tiledata::gettiletype(newtileid)) //check if side updates = necessary
        {
            chunklight::updatesunlight(c, ctpos, false);
        }

        if (chunkcoords::withinchunkbounds(ctpos))
        {
            if (ctpos.x == 0) addctiletochange(chunkpos{cpos.x-1, cpos.y}, ctilepos{chunkwidth, ctpos.y, ctpos.z}, newtileid, false);
            if (ctpos.x == chunkwidth-1) addctiletochange(chunkpos{cpos.x+1, cpos.y}, ctilepos{-1, ctpos.y, ctpos.z}, newtileid, false);
            if (ctpos.z == 0) addctiletochange(chunkpos{cpos.x, cpos.y-1}, ctilepos{ctpos.x, ctpos.y, chunkwidth}, newtileid, false);
            if (ctpos.z == chunkwidth-1) addctiletochange(chunkpos{cpos.x, cpos.y+1}, ctilepos{ctpos.x, ctpos.y, -1}, newtileid, false);
        }

        if (breakage)
        {
            uint8_t textureid = tiledata::gettileinfo(oldtile).breaktextureid;
            uint8_t glow = tiledata::gettileinfo(oldtile).glow;
            wposition tilepos = wposition(cpos.x * chunkwidth + ctpos.x, ctpos.y, cpos.y * chunkwidth + ctpos.z);

            for (int a =0 ; a < 3; a++)
            {
                //direction chardir = (-maincharcontroller::getviewdir() / 10.0f);
                float randx = utils::randint(-3, 3);
                float randz = utils::randint(-3, 3);
                randx /= 30.0f;
                randz /= 30.0f;
                particlemanager::addparticle(wposition(tilepos.x + 0.5f, tilepos.y + 0.5f, tilepos.z + 0.5f), velocity(randx, -0.05f, randz), textureid, 15, 2000, glow, 0.5f, false);
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
    else
    {
        return false;
    }
}

void chunkcontroller::explodetiles(wtilepos wtile, int32_t explosionpower)
{
    for (int x = -explosionpower; x <= explosionpower; x++)
    {
        for (int z = -explosionpower; z <= explosionpower; z++)
        {
            for (int y = -explosionpower; y <= explosionpower; y++)
            {
                if (glm::distance(glm::vec3(0.0f), glm::vec3(x,y,z)) <= explosionpower && wtile.y + y > 0 && wtile.y + y < chunkheight)
                {
                    tileid tid = gettileid(wtile + wtilepos{x,y,z});
                    if (!tiledata::needssupport(tid))
                        breaktile(wtile + wtilepos{x,y,z}); //blir debug particles fordi busker og sånt legges med - fixed
                }
            }
        }
    }
}

void chunkcontroller::breaktile(wtilepos wtile)
{
    //drop stuff?
    tileid tid = gettileid(wtile);
    if (tid > 1) //air and water cannot be broken normally
    {
        addtiletochange(wtile, 0, true);

        if (wtile.y > 0)
        {
            wtile.y--;
            tileid tid = gettileid(wtile);
            if (tiledata::needssupport(tid))
            {
                breaktile(wtile);
            }
        }
    }
}

bool chunkcontroller::chunkexists(chunkpos cpos)
{
    uint32_t id = cpostoid(cpos);
    if (chunks.find(id) == chunks.end()) return false;
    return true;
}

bool chunkcontroller::newchunk(chunkpos cpos)
{
    uint32_t id = cpostoid(cpos);

    //if (!chunkexists(cpos)) //chunk not exists in map
    //{
        //chunks.emplace(id, chunk(chunkdimensions, cpos));
        chunks.emplace(std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple(chunkdimensions, cpos));
        loadedchunks.push_back(cpos);
        return true;
    //}
    //return false;
}

bool chunkcontroller::removechunk(chunkpos cpos)
{
    chunk& chunktodelete = getchunk(cpos);
    if (chunktodelete.safetodelete())
    {
        chunktodelete.deletechunk();
        chunks.erase(cpostoid(cpos)); //any memory leaks?

        auto position = std::find(loadedchunks.begin(), loadedchunks.end(), cpos);
        if (position != loadedchunks.end())
            loadedchunks.erase(position);

        return true;
    }

    return false;
}
