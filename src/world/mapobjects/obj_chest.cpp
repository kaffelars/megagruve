#include "consts.h"
#include "obj_chest.h"

#include "texturemanager.h"
#include "map_obj_models.h"
#include "tiledata.h"

#include "scenegamehelperfunctions.h"
#include "uiinventory.h"
#include "timedfunctions.h"
#include "uiingame.h"

obj_chest::obj_chest(ctilepos ctp, chunkpos cpo, uint8_t forw, uint8_t chestsize) : map_obj(ctp, cpo, forw)
{
    hasmodel = true;
    chestinv.resizeinv(chestsize);
}

obj_chest::~obj_chest()
{
    //dtor
}

void obj_chest::addmodel(ctilepos ctp, chunkmesh& cmesh, chunklightcontainer& sunlight)
{
    //tiledata::addblock(ctp, 2, 0, 255, 255, notint, 0, 0, notint, cmesh);
    if (lidopen)
        map_obj_models::addmodel(cmesh, sunlight, ctp, 1, forwardside);
    else
        map_obj_models::addmodel(cmesh, sunlight, ctp, 0, forwardside);
}

void obj_chest::interact(mainchar& interactor)
{
    lidopen = true;
    remeshchunk();
    uiinventory::setextrainventory(chestinv);
    scenegamehelperfunctions::toggleinventory(inventorytype::chest);
    timedfunctions::addtimedfunction(500.0f, [&](){trycloselid();});
}

void obj_chest::trycloselid()
{
    if (!uiingame::showinginventory())
    {
        lidopen = false;
        remeshchunk();
    }
    else
    {
        timedfunctions::addtimedfunction(500.0f, [&](){trycloselid();});
    }
}

void obj_chest::destroy()
{
    //drop inv
    //husk å fixe remove map_obj fra chunk
}

uint8_t obj_chest::lightattenuation()
{
    return 15;
}
