#ifndef OBJ_LIGHTBULB_H
#define OBJ_LIGHTBULB_H

#include "map_obj.h"
#include "chunkmesh.h"

class obj_lightbulb : public map_obj
{
    public:
        obj_lightbulb(ctilepos ctp, chunkpos cpo, uint8_t forw);
        virtual ~obj_lightbulb();

        void addmodel(ctilepos ctp, chunkmesh& cmesh, chunklightcontainer& sunlight);
        bool passable();
        uint8_t lightattenuation();

    protected:

    private:
};

#endif // OBJ_LIGHTBULB_H
