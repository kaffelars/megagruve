#include "consts.h"
#include "obj_child.h"

obj_child::obj_child(ctilepos ctp, chunkpos cpo, std::shared_ptr<map_obj> motherptr) : map_obj(ctp, cpo, 0)
{
    mother = motherptr;
    mapobjid = 255;
}

obj_child::~obj_child()
{
    //dtor
}

void obj_child::interact(mainchar& interactor)
{
    if (interactable)
    {
        if (mother != nullptr)
        {
            mother->interact(interactor);
        }
    }
}

bool obj_child::isindirectlyinteractable()
{
    return mother->isindirectlyinteractable();
}

bool obj_child::passable()
{
    return mother->passable();
}
