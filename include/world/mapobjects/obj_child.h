#ifndef OBJ_CHILD_H
#define OBJ_CHILD_H

#include "mainchar.h"
#include "chunkmesh.h"
#include "map_obj.h"

class obj_child : public map_obj
{
    public:
        obj_child(ctilepos ctp, chunkpos cpo, std::shared_ptr<map_obj> motherptr);
        virtual ~obj_child();

        void interact(mainchar& interactor);

        bool interactable {true};

        bool isindirectlyinteractable();

        bool passable();
        uint8_t lightattenuation();

    protected:

    private:
};

#endif // OBJ_CHILD_H
