#ifndef VOXELMODELS_H
#define VOXELMODELS_H

#include "voxelmodel.h"
#include "tiledata.h"
#include "utils.h"

namespace voxelmodels
{
    void initialize();
    voxelmodel& getvoxelmodel(std::string id);
    voxelmodel& getvoxelmodel(uint32_t id);
};

#endif // VOXELMODELS_H
