#include "consts.h"

#include "obj_lightbulb.h"

#include "texturemanager.h"
#include "map_obj_models.h"
#include "tiledata.h"

obj_lightbulb::obj_lightbulb(ctilepos ctp, chunkpos cpo, uint8_t forw) : map_obj(ctp, cpo, forw)
{
    //ctor
}

obj_lightbulb::~obj_lightbulb()
{
    //dtor
}

void obj_lightbulb::addmodel(ctilepos ctp, chunkmesh& cmesh)
{
    map_obj_models::addmodel(cmesh, ctp, 8, forwardside);
}


bool obj_lightbulb::passable()
{
    return true;
}
