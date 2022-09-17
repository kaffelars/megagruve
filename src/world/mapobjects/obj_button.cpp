#include "consts.h"
#include "obj_button.h"

#include "chunktilemanager.h"
#include "map_obj_models.h"

obj_button::obj_button(ctilepos ctp, chunkpos cpo, uint8_t forw) : map_obj(ctp, cpo, forw)
{
    //ctor
}

obj_button::~obj_button()
{
    //dtor
}

void obj_button::addmodel(ctilepos ctp, chunkmesh& cmesh, chunklightcontainer& sunlight, chunklightcontainer& tilelight)
{
    map_obj_models::addmodel(cmesh, sunlight, tilelight, ctp, 7, forwardside);
}

void obj_button::interact(mainchar& interactor)
{
    chunktilemanager::interactobjaround(cpos, ctpos, -sideoffsets[forwardside], interactor);
}

bool obj_button::passable()
{
    return true;
}

uint8_t obj_button::lightattenuation()
{
    return 0;
}
