#include "consts.h"
#include "chunkcontroller.h"

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

    struct updateside
    {
        chunkpos maincpos;
        ctilepos maintpos;

        uint8_t side;

        chunkpos nbourcpos;
        ctilepos nbourtpos;
    };

    struct changetile
    {
        wtilepos wpos;
        tileid tid;
    };

    int32_t counter = 0;

    std::vector<updateside> sidestoupdate; //sides som skal updates (på sidene)

    std::vector<changetile> tilestochange; //tiles som skal changes


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
    counter++;
    if (counter > 1000000000) counter = 0;

    chunkpos centerchunk = wpostocpos(maincharposition);

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
    changetiles();

    updatesides(); //(tries to) updates sides that couldn't be updated in changetiles

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

tileid chunkcontroller::gettileid(wtilepos wtpos)
{
    chunkpos cpos = wpostocpos(wtpos);
    if (chunkexists(cpos))
    {
        chunk& c = getchunk(cpos);
        chunk::ctags ctag = c.gettag();
        if (ctag == chunk::C_READY || ctag == chunk::C_REMESHING)
        {
            ctilepos ctpos = wpostoctilepos(wtpos);
            return c.gettile(ctpos);
        }
    }

    return 0;
}

bool chunkcontroller::ischunkvisible(chunk& c) //not good when looking down
{
    wposition mcharpos = maincharcontroller::getmaincharposition();
    chunkpos curchunk = wpostocpos(mcharpos);
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

void chunkcontroller::renderchunk(chunkpos cpos)
{
    if (!chunkexists(cpos))
        newchunk(cpos);

    chunk& c = getchunk(cpos);
    chunk::ctags ctag = c.gettag();

    c.counter = counter;

    if (threadcounter < maxthreads && ctag == chunk::C_READY && c.needsremesh())
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
        }
    }
    else
    {
        //std::cout << chunkmeshynum << "fsef\n";
        if (threadcounter < maxthreads)
        {
            if (ctag == chunk::C_START) //mutex
            {
                threadcounter++;
                c.settag(chunk::C_GENERATING);
                auto t = std::thread(generatechunk, std::ref(c));
                t.detach();
                //generatechunk(c);
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

bool chunkcontroller::withinchunkbounds(ctilepos cpos)
{
    if (cpos.x < 0 || cpos.x > chunkwidth-1) return false;
    if (cpos.y < 0 || cpos.y > chunkheight-1) return false;
    if (cpos.z < 0 || cpos.z > chunkwidth-1) return false;
    return true;
}

void chunkcontroller::addtiletochange(wtilepos wtile, tileid newtileid)
{
    tilestochange.emplace_back(changetile{wtile, newtileid});
}

void chunkcontroller::changetiles()
{
    if (tilestochange.empty()) return;

    auto vit = tilestochange.begin();
    while (vit != tilestochange.end())
    {
        if (changewtile((*vit).wpos, (*vit).tid))
        {
            vit = tilestochange.erase(vit);
        }
        else
        {
            ++vit;
        }
    }
}

bool chunkcontroller::changewtile(wtilepos wtile, tileid newtileid)
{
    chunkpos cpos = wpostocpos(wtile);
    if (!chunkexists(cpos)) return false;
    chunk& c = getchunk(cpos);
    if (c.gettag() == chunk::C_READY)
    {
        ctilepos ctpos = wtilepostoctilepos(wtile);
        tileid oldtile = c.gettile(ctpos);
        c.settile(ctpos, newtileid);
        //std::cout << wtile.x << " " << wtile.y << " " << wtile.z << "\n";
        //std::cout << ctpos.x << " " << ctpos.y << " " << ctpos.z << "\n";
        c.setremeshy(ctpos.y);

        if (tiledata::gettiletype(oldtile) != tiledata::gettiletype(newtileid)) //check if side updates = necessary
        {
            updatesunlight(c, ctpos, false);
            addsidestoupdatearound(cpos, ctpos);
        }

        return true;
    }
    else
    {
        return false;
    }
}

void chunkcontroller::breaktile(wtilepos wtile)
{
    //drop stuff?
    addtiletochange(wtile, 0);
}

void chunkcontroller::addsidestoupdatearound(chunkpos cpos, ctilepos ctpos) //adding sides to update to side update queue around tile provided
{
    //sidestoupdate.push_back({cpos, ctpos});//main tile

    chunk& c = getchunk(cpos);
    tileid tid = c.gettile(ctpos);

    for (int a = 0; a < 6; a++)
    {
        ctilepos neighbour = ctpos + sideoffsets[a];
        if (withinchunkbounds(neighbour))
        {
            tileid ntid = c.gettile(neighbour);
            if (tiledata::renderside(tid, ntid, tiledata::sideflags[a])) c.setside(ctpos, tiledata::sideflags[a], true);
            else c.setside(ctpos, tiledata::sideflags[a], false);
            if (tiledata::renderside(ntid, tid, tiledata::oppositesideflags[a])) c.setside(neighbour, tiledata::oppositesideflags[a], true);
            else c.setside(neighbour, tiledata::oppositesideflags[a], false);

            c.setremeshy(ctpos.y);
        }
        else
        {
            if (neighbour.y >= 0 && neighbour.y < chunkheight)
            {
                wtilepos wtpos = cposctilepostowtilepos(cpos, ctpos) + sideoffsets[a];
                sidestoupdate.emplace_back(updateside{.maincpos=cpos, .maintpos=ctpos, .side=a, .nbourcpos=wtilepostocpos(wtpos), .nbourtpos=wtilepostoctilepos(wtpos)});
            }
        }
    }
}



void chunkcontroller::updatesides() //fucked?
{
    if (sidestoupdate.empty()) return;

    auto vit = sidestoupdate.begin();
    while (vit != sidestoupdate.end())
    {
        bool erased =false;
        if (chunkexists(vit->maincpos) && chunkexists(vit->nbourcpos))
        {
            chunk& c = getchunk(vit->maincpos);
            chunk& n = getchunk(vit->nbourcpos);
            if (c.gettag() == chunk::C_READY && n.gettag() == chunk::C_READY)
            {
                tileid ctid = c.gettile(vit->maintpos);
                tileid ntid = c.gettile(vit->nbourtpos);

                /*std::cout << vit->maintpos.x << " " << vit->maintpos.y << " " << vit->maintpos.z << "\n";
                std::cout << vit->nbourtpos.x << " " << vit->nbourtpos.y << " " << vit->nbourtpos.z << " s\n";

                std::cout << vit->maincpos.x << " " << vit->maincpos.y << "\n";
                std::cout << vit->nbourcpos.x << " " << vit->nbourcpos.y << " s\n";*/

                uint8_t side = vit->side;

                if (tiledata::renderside(ctid, ntid, tiledata::sideflags[side])) c.setside(vit->maintpos, tiledata::sideflags[side], true);
                else c.setside(vit->maintpos, tiledata::sideflags[side], false);
                if (tiledata::renderside(ntid, ctid, tiledata::oppositesideflags[side])) n.setside(vit->nbourtpos, tiledata::oppositesideflags[side], true);
                else n.setside(vit->nbourtpos, tiledata::oppositesideflags[side], false);

                c.setremeshy(vit->maintpos.y);
                n.setremeshy(vit->nbourtpos.y);

                vit = sidestoupdate.erase(vit);
                erased  =true;
            }
        }
        if (!erased) ++vit;
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
        //sjekk om den blir updated i annen thread elns
        return true;
    }

    /*if (chunks.find(id) != chunks.end()) //chunk exists in map
    {
        //deletos
        if (getchunk(cpos).safetodelete())
        {
            chunks.erase(id); //any memory leaks?

            auto position = std::find(loadedchunks.begin(), loadedchunks.end(), cpos);
            if (position != loadedchunks.end())
                loadedchunks.erase(position);
            //sjekk om den blir updated i annen thread elns
            return true;
        }
    }*/
    return false;
}
