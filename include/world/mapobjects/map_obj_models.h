#ifndef MAP_OBJ_MODELS_H
#define MAP_OBJ_MODELS_H

#include "chunkmesh.h"

namespace map_obj_models
{
    void initialize();
    void addmodel(chunkmesh& cm, ctilepos ctpos, uint32_t modelid, uint8_t forwardside, int32_t texid = -1);

};

#endif // MAP_OBJ_MODELS_H
