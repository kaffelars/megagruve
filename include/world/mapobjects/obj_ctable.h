#ifndef OBJ_CTABLE_H
#define OBJ_CTABLE_H

#include "map_obj.h"
#include "mainchar.h"

class obj_ctable : public map_obj
{
    public:
        obj_ctable(ctilepos ctp, chunkpos cpo, uint8_t forw);
        virtual ~obj_ctable();

        void addmodel(ctilepos ctp, chunkmesh& cmesh, chunklightcontainer& sunlight);
		void interact(mainchar& interactor);
		void destroy();
		uint8_t lightattenuation();

    protected:

    private:
};

#endif // OBJ_CTABLE_H
