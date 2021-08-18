#include "consts.h"
#include "chunk.h"

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

void chunk::deletechunk()
{
    for (int a = 0; a < chunkmeshynum; a++)
    {
        cmesh[a][0].cleanbuffers();
        cmesh[a][1].cleanbuffers();
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

uint32_t chunk::gettilecoord(ctilepos tpos)
{
    return (tpos.x+1) + (chunkwidth+2)*((tpos.z+1) + tpos.y*(chunkwidth+2));
}

void chunk::setsunlight(ctilepos tpos, uint8_t value)
{
    tilelight[get3dcoord(tpos)].sunlight = value / 16;
}

uint8_t chunk::getsunlight(ctilepos tpos)
{
    return tilelight[get3dcoord(tpos)].sunlight * 17; //for å mappe til 0 - 255
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
}

tileid chunk::gettile(ctilepos tpos)
{
    return tileids[gettilecoord(tpos)];
}
void chunk::settile(ctilepos tpos, tileid value)
{
    tileids[gettilecoord(tpos)] = value;
}
uint8_t chunk::getsides(ctilepos tpos)
{
    return tilesides[get3dcoord(tpos)];
}
void chunk::setsides(ctilepos tpos, uint8_t sideval)
{
    tilesides[get3dcoord(tpos)] = sideval;
}
void chunk::addside(ctilepos tpos, tiledata::tilesides side)
{
    int sidez = getsides(tpos);
    sidez |= side;
    setsides(tpos, sidez);
}

void chunk::setside(ctilepos tpos, tiledata::tilesides side, bool toggleon)
{
    if (toggleon)
    {
        addside(tpos, side);
    }
    else
    {
        int sidez = getsides(tpos);
        sidez &= ~side;
        setsides(tpos, sidez);
    }
}

void chunk::addtile(tileid value)
{
    tileids.push_back(value);
}

void chunk::addside()
{
    tilesides.push_back(0);
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
    if (gettag() == C_START || gettag()==C_READY) return true; //burde være noenlunde trygt
    return false;
}

void chunk::render()
{
    for (int a =0; a < chunkmeshynum; a++)
    {
        glUniform3f(shadercontroller::getuniformid("vpos"), cpos.x*cdims.x, 0.0f, cpos.y*cdims.z); //y er 0 fordi ypos blir meshet inn
        cmesh[a][getactivemesh(a)].render();

    }
}
