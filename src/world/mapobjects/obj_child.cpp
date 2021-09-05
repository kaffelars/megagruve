#include "consts.h"
#include "obj_child.h"

obj_child::obj_child(ctilepos ctp, chunkpos cpo) : map_obj(ctp, cpo, 0)
{
    //ctor
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
