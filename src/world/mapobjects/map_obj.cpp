#include "consts.h"
#include "map_obj.h"

#include "chunkcontroller.h"

map_obj::map_obj(ctilepos ctp, chunkpos cpo, uint8_t forw) : ctpos{ctp}, cpos{cpo}, forwardside{forw}
{

}

void map_obj::addmodel(ctilepos ctp, chunkmesh& cmesh)
{

}

void map_obj::interact(mainchar& interactor)
{

}

void map_obj::destroy()
{

}

void map_obj::remeshchunk()
{
    chunkcontroller::addremesh(cpos, ctpos);
}
