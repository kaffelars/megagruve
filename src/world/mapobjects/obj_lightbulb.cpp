#include "consts.h"

#include "obj_lightbulb.h"

#include "texturemanager.h"
#include "map_obj_models.h"
#include "tiledata.h"
#include "chunktilemanager.h"

obj_lightbulb::obj_lightbulb(ctilepos ctp, chunkpos cpo, uint8_t forw) : map_obj(ctp, cpo, forw)
{
    //ctor
}

obj_lightbulb::~obj_lightbulb()
{
    //dtor
}

void obj_lightbulb::addmodel(ctilepos ctp, chunkmesh& cmesh, chunklightcontainer& sunlight, chunklightcontainer& tilelight)
{
    map_obj_models::addmodel(cmesh, sunlight, tilelight, ctp, 8, forwardside);
}

void obj_lightbulb::create()
{
    chunktilemanager::addtilelight(ctpos, cpos, 15);
}


bool obj_lightbulb::passable()
{
    return true;
}

uint8_t obj_lightbulb::lightattenuation()
{
    return 0;
}
