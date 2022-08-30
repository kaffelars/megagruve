#include "consts.h"
#include "chunkcontroller.h"

#include "chunkcoords.h"

#include "biomecontroller.h"
#include "particlemanager.h"
#include "chunkgenerator.h"
#include "defaultgenerator.h"
#include "newgenerator.h"
#include "chunklight.h"
#include "chunkwatermanager.h"
#include "environment.h"

#include "chunktilemanager.h"

namespace chunkcontroller
{
    uint32_t cpostoid(chunkpos cpos);
    bool newchunk(chunkpos cpos);
    bool removechunk(chunkpos cpos);

    std::unordered_map<uint32_t, chunk> chunks;
    dimensions chunkdimensions = glm::ivec3(chunkwidth,chunkheight,chunkwidth);


    std::atomic<uint32_t> threadcounter = 0;
    std::vector<chunkpos> loadedchunks; //loop heller bare gjennom elementene i unordered map
    int32_t chunksrendered = 0;


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


    //std::unique_ptr<chunkgenerator> currentchunkgenerator = std::make_unique<defaultgenerator>();
    std::unique_ptr<chunkgenerator> currentchunkgenerator = std::make_unique<newgenerator>();
}

void chunkcontroller::preparenewworld()
{
    //clear any old world
    chunkwatermanager::clearactivewatertiles();
    chunktilemanager::cleartilestochange();
    environment::resetenvironment();
    particlemanager::deleteallparticles();
    for (auto& c: chunks)
    {
        c.second.deletechunk();
    }
    chunks.clear();
    loadedchunks.clear();
}

void chunkcontroller::adddecoration(chunkpos cpos, ctilepos ctpos, uint32_t voxelmodelid)
{
    decoratemutex.lock();
    decorations.push_back(cdecorate{voxelmodelid, cpos, ctpos});
    decoratemutex.unlock();
}

bool chunkcontroller::chunkexists(chunkpos cpos)
{
    uint32_t id = cpostoid(cpos);
    if (chunks.find(id) == chunks.end()) return false;
    return true;
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

    chunktilemanager::changetiles();

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

void chunkcontroller::preparestartingarea(wposition mcharposition)
{
    chunkpos centerchunk = chunkpos{mcharposition.x / chunkdimensions.x, mcharposition.z / chunkdimensions.z};

    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            //chunkpos cp = centerchunk + chunkpos{x,y};
            //std::cout << cp.x << " -- " << cp.y << "\n";

            newchunk(centerchunk + chunkpos{x,y});
            getchunk(centerchunk + chunkpos{x,y}).settag(chunk::C_GENERATING);
            currentchunkgenerator->generatechunk(getchunk(centerchunk + chunkpos{x,y}));
            meshwholechunk(getchunk(centerchunk + chunkpos{x,y}));
            getchunk(centerchunk + chunkpos{x,y}).setallvbos();
            getchunk(centerchunk + chunkpos{x,y}).settag(chunk::C_READY);
            threadcounter+=2;
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
        if (ctag == chunk::C_READY || ctag == chunk::C_REMESHING || ctag == chunk::C_REMESHED)
        {
            ctilepos ctpos = chunkcoords::wpostoctilepos(wtpos);
            return c.getalllight(ctpos);
        }
    }

    return chunk::tlight{0,0};
}

void chunkcontroller::addremesh(chunkpos cpos, ctilepos ctpos) //brukes fra map_obj
{
    if (chunkexists(cpos))
    {
        chunk& c = getchunk(cpos);
        chunk::ctags ctag = c.gettag();
        if (ctag == chunk::C_READY || ctag == chunk::C_REMESHED)
        {
            addremesh(c, ctpos.y);
        }
    }
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

    //lazy fix for når man ser down
    if (c.cpos.x > curchunk.x -2 && c.cpos.x <= curchunk.x +2) return true;
    if (c.cpos.y > curchunk.y -2 && c.cpos.y <= curchunk.y +2) return true;

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
            if (ctag == chunk::C_READY)
            {
                chunktilemanager::checkoutsidetiles(c);
            }
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






void chunkcontroller::addremesh(chunk& c, ytile yt)
{
    c.setremeshy(yt);
    if (yt > 1) c.setremeshy(yt-1);
    if (yt < chunkheight-2) c.setremeshy(yt+1);
}

void chunkcontroller::interactobj(wtilepos wtpos, mainchar& mchar)
{
    chunkpos cpos = chunkcoords::wtilepostocpos(wtpos);
    ctilepos ctpos = chunkcoords::wtilepostoctilepos(wtpos);
    interactobj(cpos, ctpos, mchar);
}

void chunkcontroller::interactobj(chunkpos cpos, ctilepos ctpos, mainchar& mchar)
{
    if (chunkexists(cpos))
    {
        chunk& c = getchunk(cpos);
        chunk::ctags ctag = c.gettag();
        if (ctag == chunk::C_READY || ctag == chunk::C_REMESHING)
        {
            if (c.gettile(ctpos) == 255) //hvis obj, legg inn sjekk om obj exists et sted? i chunk::getmapobj probs
                c.interactobj(ctpos, mchar);
        }
    }
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
