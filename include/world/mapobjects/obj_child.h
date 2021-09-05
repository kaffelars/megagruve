#ifndef OBJ_CHILD_H
#define OBJ_CHILD_H

#include "mainchar.h"
#include "chunkmesh.h"
#include "map_obj.h"

class obj_child : public map_obj
{
    public:
        obj_child(ctilepos ctp, chunkpos cpo);
        virtual ~obj_child();

        void interact(mainchar& interactor);

        bool interactable {true};

    protected:

    private:
};

#endif // OBJ_CHILD_H
