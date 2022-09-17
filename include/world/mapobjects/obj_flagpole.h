#ifndef OBJ_FLAGPOLE_H
#define OBJ_FLAGPOLE_H

#include "chunkmesh.h"
#include "mainchar.h"
#include "map_obj.h"

class obj_flagpole : public map_obj
{
    public:
        obj_flagpole(ctilepos ctp, chunkpos cpo, uint8_t forw);
        virtual ~obj_flagpole();

        void addmodel(ctilepos ctp, chunkmesh& cmesh, chunklightcontainer& sunlight, chunklightcontainer& tilelight);
		void interact(mainchar& interactor);
		void destroy();
		uint8_t lightattenuation();

		int32_t flagtextureid {-1};
		int32_t flagitemid {-1};
    protected:

    private:
};

#endif // OBJ_FLAGPOLE_H
