#ifndef VOXELMODELS_H
#define VOXELMODELS_H

#include "voxelmodel.h"
#include "tiledata.h"

namespace voxelmodels
{
    void initialize();
    voxelmodel& getvoxelmodel(std::string id);
};

#endif // VOXELMODELS_H
