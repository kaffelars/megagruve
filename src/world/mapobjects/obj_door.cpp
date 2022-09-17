#include "consts.h"
#include "obj_door.h"

#include "map_obj_models.h"

obj_door::obj_door(ctilepos ctp, chunkpos cpo, uint8_t forw) : map_obj(ctp, cpo, forw)
{
    hasmodel = true;
    isopen = false;
}

obj_door::~obj_door()
{
    //dtor
}

void obj_door::addmodel(ctilepos ctp, chunkmesh& cmesh, chunklightcontainer& sunlight, chunklightcontainer& tilelight)
{
    //tiledata::addblock(ctp, 2, 0, 255, 255, notint, 0, 0, notint, cmesh);
    if (isopen)
        map_obj_models::addmodel(cmesh, sunlight, tilelight, ctp, 6, forwardside);
    else
        map_obj_models::addmodel(cmesh, sunlight, tilelight, ctp, 5, forwardside);
}

bool obj_door::isindirectlyinteractable()
{
    return true;
}

void obj_door::interact(mainchar& interactor)
{
    isopen = !isopen;
    remeshchunk();
}

bool obj_door::passable()
{
    return isopen;
}

uint8_t obj_door::lightattenuation()
{
    return 15;
}
