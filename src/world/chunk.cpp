#include "consts.h"
#include "chunk.h"

#include "map_obj_manager.h"

chunk::chunk(dimensions dims, chunkpos pos)
{
    cdims = dims;
    cpos = pos;
    chunktag = C_START;
    std::fill_n(activecmesh, chunkmeshynum, false);
    std::fill_n(remesh, chunkmeshynum, false);
}

chunk::~chunk()
{
    //dtor
}

std::shared_ptr<map_obj>& chunk::getmapobj(ctilepos ctpos)
{
    return chunk_objs.at(get3dcoord(ctpos));
}

void chunk::deletechunk()
{
    for (int a = 0; a < chunkmeshynum; a++)
    {
        cmesh[a][0].cleanbuffers();
        cmesh[a][1].cleanbuffers();

        wmesh[a][0].cleanbuffers();
        wmesh[a][1].cleanbuffers();
    }
}

void chunk::settag(ctags ctag)
{
    tagmutex.lock();
    chunktag = ctag;
    tagmutex.unlock();
}

chunk::ctags chunk::gettag()
{
    tagmutex.lock();
    ctags ctag = chunktag;
    tagmutex.unlock();


    return ctag;
}

bool chunk::getremesh(int toremesh)
{
    remeshmutex.lock();
    bool mesho = remesh[toremesh];
    remeshmutex.unlock();

    return mesho;
}

void chunk::setremesh(int toremesh, bool meshthis)
{
    remeshmutex.lock();
    remesh[toremesh] = meshthis;
    remeshmutex.unlock();
}

void chunk::setremeshy(ytile ycoord)
{
    setremesh(ycoord / chunkmeshheight);
}

bool chunk::needsremesh()
{
    bool needsremesh = false;
    remeshmutex.lock();
    for (int a = 0; a < chunkmeshynum; a++)
    {
        if (remesh[a])
        {
            needsremesh = true;
        }
    }
    remeshmutex.unlock();

    return needsremesh;
}

void chunk::addchunkobj(ctilepos ctpos, uint8_t mapobjid, uint8_t forwardside)
{
    map_obj_manager::addmapobj(*this, ctpos, mapobjid, forwardside);
}

void chunk::removechunkobj(ctilepos ctpos)
{
    getmapobj(ctpos)->destroy();
    chunk_objs.erase(get3dcoord(ctpos));
}

void chunk::interactobj(ctilepos ctpos, mainchar& mchar)
{
    getmapobj(ctpos)->interact(mchar);
}


void chunk::addlight()
{
    tilelight.push_back(tlight{0,0});
}

uint32_t chunk::get2dcoord(chtilepos thpos)
{
    return thpos.x + chunkwidth*(thpos.y);
}

uint32_t chunk::get3dcoord(ctilepos tpos)
{
    return tpos.x + chunkwidth*(tpos.z + tpos.y*chunkwidth);
}

uint32_t chunk::getbiomecoord(chtilepos thpos)
{
    return (thpos.x+1) + (chunkwidth+2)*((thpos.y+1));
}

uint32_t chunk::gettilecoord(ctilepos tpos)
{
    return (tpos.x+1) + (chunkwidth+2)*((tpos.z+1) + tpos.y*(chunkwidth+2));
}

void chunk::setsunlight(ctilepos tpos, uint8_t value)
{
    tilelight[gettilecoord(tpos)].sunlight = value / 16;
}

uint8_t chunk::getsunlight(ctilepos tpos)
{
    return tilelight[gettilecoord(tpos)].sunlight * 17; //for � mappe til 0 - 255
}

chunk::tlight chunk::getalllight(ctilepos tpos)
{
    return tilelight[gettilecoord(tpos)];
}

void chunk::setallvbos()
{
    for (int a = 0; a < chunkmeshynum; a++)
        setonevbo(a);
}

void chunk::setremeshedvbos()
{
    for (int a = 0; a < chunkmeshynum; a++)
    {
        if (getremesh(a))
        {
            setonevbo(a);
            setremesh(a, false);
        }
    }
}

void chunk::setonevbo(uint8_t meshnum)
{
    toggleactivemesh(meshnum);
    cmesh[meshnum][getactivemesh(meshnum)].setvbos();
    cmesh[meshnum][!getactivemesh(meshnum)].cleanall();

    wmesh[meshnum][getactivemesh(meshnum)].setvbos();
    wmesh[meshnum][!getactivemesh(meshnum)].cleanall();
}

void chunk::setbiome(biomedata b, chtilepos chpos)
{
    biomes[getbiomecoord(chpos)] = b;
}

chunk::biomedata chunk::getbiome(chtilepos chpos)
{
    return biomes[getbiomecoord(chpos)];
}

chunk::biomedata chunk::getbiome(ctilepos ctpos)
{
    //debug stuff
    /*if (ctpos.x < -1) std::cout << "x binus " << ctpos.x;
    if (ctpos.z < -1) std::cout << "z binus " << ctpos.z;
    if (ctpos.x > chunkwidth) std::cout << "x bakrus " << ctpos.x;
    if (ctpos.z > chunkwidth) std::cout << "z bakrus " << ctpos.z;*/

    chunk::biomedata b = biomes[getbiomecoord(chtilepos{ctpos.x, ctpos.z})];
    if (ctpos.y < 120)
    {
        if (120 - ctpos.y > b.temperature) b.temperature = 0;
        else b.temperature -= (120 - ctpos.y);
    }
    return b;
}

void chunk::addbiome()
{
    biomes.push_back(biomedata{0,0});
}

tileid chunk::gettile(ctilepos tpos)
{
    //debug stuff
    /*if (tpos.x < -1) std::cout << "x minus " << tpos.x;
    if (tpos.z < -1) std::cout << "z minus " << tpos.z;
    if (tpos.x > chunkwidth) std::cout << "x makrus " << tpos.x;
    if (tpos.z > chunkwidth) std::cout << "z makrus " << tpos.z;
    if (tpos.y < 0) std::cout << "y minus " << tpos.y;
    if (tpos.y > chunkheight-1) std::cout << "y makrus " << tpos.y;*/
    return tileids[gettilecoord(tpos)];
}
void chunk::settile(ctilepos tpos, tileid value)
{
    tileids[gettilecoord(tpos)] = value;
}


void chunk::addtile(tileid value)
{
    tileids.push_back(value);
}


uint8_t chunk::getactivemesh(uint8_t meshnum)
{
    return activecmesh[meshnum];
}

uint8_t chunk::getinactivemesh(uint8_t meshnum)
{
    return !activecmesh[meshnum];
}

void chunk::toggleactivemesh(uint8_t meshnum)
{
    activecmesh[meshnum] = !activecmesh[meshnum];
}

void chunk::sethighest(chtilepos thpos, ytile y)
{
    highesttile[get2dcoord(thpos)] = y;
}

ytile chunk::gethighest(chtilepos thpos)
{
    return highesttile[get2dcoord(thpos)];
}

void chunk::addhighest(ytile value)
{
    highesttile.push_back(value);
}

bool chunk::safetodelete()
{
    if (gettag() == C_START || gettag()==C_READY) return true; //burde v�re noenlunde trygt
    return false;
}

void chunk::render()
{
    for (int a =0; a < chunkmeshynum; a++)
    {
        if (!cmesh[a][getactivemesh(a)].isempty())
        {
            glUniform3f(shadercontroller::getuniformid("vpos"), cpos.x*cdims.x, 0.0f, cpos.y*cdims.z); //y er 0 fordi ypos blir meshet inn
            cmesh[a][getactivemesh(a)].render();
        }
    }
}

void chunk::renderwater()
{
    for (int a =0; a < chunkmeshynum; a++)
    {
        if (!wmesh[a][getactivemesh(a)].isempty())
        {
            glUniform3f(shadercontroller::getuniformid("vpos"), cpos.x*cdims.x, 0.0f, cpos.y*cdims.z); //y er 0 fordi ypos blir meshet inn
            wmesh[a][getactivemesh(a)].render();
        }
    }
}
