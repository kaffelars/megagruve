#include "consts.h"
#include "obj_ctable.h"

#include "map_obj_models.h"

obj_ctable::obj_ctable(ctilepos ctp, chunkpos cpo, uint8_t forw) : map_obj(ctp, cpo, forw)
{
    //ctor
}

obj_ctable::~obj_ctable()
{
    //dtor
}

void obj_ctable::addmodel(ctilepos ctp, chunkmesh& cmesh, chunklightcontainer& sunlight, chunklightcontainer& tilelight)
{
    map_obj_models::addmodel(cmesh, sunlight, tilelight, ctp, 4, forwardside);
}

void obj_ctable::interact(mainchar& interactor)
{

}

void obj_ctable::destroy()
{
    //drop inv
    //husk å fixe remove map_obj fra chunk
}

uint8_t obj_ctable::lightattenuation()
{
    return 8;
}
