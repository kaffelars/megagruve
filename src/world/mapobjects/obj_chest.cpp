#include "consts.h"
#include "obj_chest.h"

#include "texturemanager.h"
#include "map_obj_models.h"
#include "tiledata.h"

obj_chest::obj_chest(ctilepos ctp, chunkpos cpo, uint8_t forw) : map_obj(ctp, cpo, forw)
{
    hasmodel = true;
}

obj_chest::~obj_chest()
{
    //dtor
}

void obj_chest::addmodel(ctilepos ctp, chunkmesh& cmesh)
{
    //tiledata::addblock(ctp, 2, 0, 255, 255, notint, 0, 0, notint, cmesh);
    if (lidopen)
        map_obj_models::addmodel(cmesh, ctp, 1, forwardside);
    else
        map_obj_models::addmodel(cmesh, ctp, 0, forwardside);
}

void obj_chest::interact(mainchar& interactor)
{
    lidopen = !lidopen;
    remeshchunk();
}

void obj_chest::destroy()
{
    //drop inv
    //husk å fixe remove map_obj fra chunk
}
