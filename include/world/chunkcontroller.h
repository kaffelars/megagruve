#ifndef CHUNKCONTROLLER_H
#define CHUNKCONTROLLER_H

#include "chunk.h"
#include "tiledata.h"
#include "utils.h"
#include "randfunc.h"
#include "maincharcontroller.h"
#include "mainchar.h"
#include "camera.h"
#include "settings.h"
#include "voxelmodels.h"
#include "voxelmodel.h"

namespace chunkcontroller
{
    chunk& getchunk(chunkpos cpos);
    //void generatechunk(chunk& c);
    //void generatechunksides(chunk& c, chunk& sidechunk, uint8_t side);
    //void decorate(chunk& c);
    void adddecoration(chunkpos cpos, ctilepos ctpos, uint32_t voxelmodelid);
    //void addvoxelmodel(chunk& c, ctilepos ctpos, uint32_t voxelmodelid, bool cgenerator);

    void meshwholechunk(chunk& c);
    void meshchunkpart(chunk& c, uint8_t cpart);
    void remeshchunk(chunk& c);

    void addremesh(chunkpos cpos, ctilepos ctpos);
    void addremesh(chunk& c, ytile yt);

    bool ischunkvisible(chunk& c);

    bool chunkexists(chunkpos cpos);


    void interactobj(wtilepos wtpos, mainchar& mchar);
    void interactobj(chunkpos cpos, ctilepos ctpos, mainchar& mchar);

    void updatesunlight(chunk& c, ctilepos ctpos, bool initial);

    tileid gettileid(wtilepos wtpos);
    tileid gettileid(wposition wtpos);
    chunk::tlight getlight(wtilepos wtpos);

    void updatechunks();
    int loadedchunksnum();

    void renderchunks(direction dir, wposition maincharposition);
    int32_t getchunksrendered();

    extern std::atomic<uint32_t> threadcounter;

    void renderchunk(chunkpos cpos);
    void renderwater();
};

#endif // CHUNKCONTROLLER_H
