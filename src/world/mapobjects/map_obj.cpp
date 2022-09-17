#include "consts.h"
#include "map_obj.h"

#include "chunkcontroller.h"

map_obj::map_obj(ctilepos ctp, chunkpos cpo, uint8_t forw) : ctpos{ctp}, cpos{cpo}, forwardside{forw}
{

}

void map_obj::addmodel(ctilepos ctp, chunkmesh& cmesh, chunklightcontainer& sunlight, chunklightcontainer& tilelight)
{

}

void map_obj::interact(mainchar& interactor)
{

}

void map_obj::destroy()
{

}

void map_obj::create()
{

}

uint8_t map_obj::lightattenuation()
{
    return 0;
}

void map_obj::remeshchunk()
{
    chunkcontroller::addremesh(cpos, ctpos);
}

bool map_obj::passable()
{
    return false;
}

bool map_obj::isindirectlyinteractable()
{
    return false;
}
