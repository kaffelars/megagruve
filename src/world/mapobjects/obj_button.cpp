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

void obj_button::addmodel(ctilepos ctp, chunkmesh& cmesh)
{
    map_obj_models::addmodel(cmesh, ctp, 7, forwardside);
}

void obj_button::interact(mainchar& interactor)
{
    chunktilemanager::interactobjaround(cpos, ctpos, -sideoffsets[forwardside], interactor);
}
