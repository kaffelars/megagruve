#ifndef OBJ_BUTTON_H
#define OBJ_BUTTON_H

#include "map_obj.h"
#include "chunkmesh.h"
#include "mainchar.h"

class obj_button : public map_obj
{
    public:
        obj_button(ctilepos ctp, chunkpos cpo, uint8_t forw);
        virtual ~obj_button();

        void addmodel(ctilepos ctp, chunkmesh& cmesh, chunklightcontainer& sunlight, chunklightcontainer& tilelight);
		void interact(mainchar& interactor);
		bool passable();
		uint8_t lightattenuation();

    protected:

    private:
};

#endif // OBJ_BUTTON_H
