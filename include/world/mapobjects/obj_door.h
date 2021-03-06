#ifndef OBJ_DOOR_H
#define OBJ_DOOR_H

#include "map_obj.h"
#include "mainchar.h"
#include "chunkmesh.h"

class obj_door : public map_obj
{
    public:
        obj_door(ctilepos ctp, chunkpos cpo, uint8_t forw);
        virtual ~obj_door();

        void addmodel(ctilepos ctp, chunkmesh& cmesh);
		void interact(mainchar& interactor);
		bool passable();
		bool isindirectlyinteractable();

        bool isopen;

    protected:

    private:
};

#endif // OBJ_DOOR_H
