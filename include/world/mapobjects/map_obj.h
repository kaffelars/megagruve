#ifndef MAP_OBJ_H
#define MAP_OBJ_H

#include "mainchar.h"
#include "chunkmesh.h"
#include "chunklightcontainer.h"

class map_obj
{
    public:
        map_obj(ctilepos ctp, chunkpos cpo, uint8_t forw);
		virtual ~map_obj() = default;
		virtual void addmodel(ctilepos ctp, chunkmesh& cmesh, chunklightcontainer& sunlight, chunklightcontainer& tilelight); //adds model to chunk mesh
		virtual void interact(mainchar& interactor);//when interacting (default right mouse button)
		virtual void destroy(); //when destroyed
		virtual void create();//when placed
		virtual bool passable(); //is passable?
		void remeshchunk();//orders chunk to remesh
		virtual bool isindirectlyinteractable(); //can be interacted with through e.g. buttons?
		virtual uint8_t lightattenuation(); //attenuates light?

		ctilepos ctpos {ctilepos{0,0,0}};
		chunkpos cpos {chunkpos{0,0}};
		uint8_t forwardside {0};

		uint8_t mapobjid {0};

		std::shared_ptr<map_obj> mother {nullptr};
		std::vector<std::shared_ptr<map_obj>> children;

		bool hasmodel {false};
    protected:

    private:
};

#endif // MAP_OBJ_H
