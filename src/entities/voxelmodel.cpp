#include "consts.h"
#include "voxelmodel.h"

voxelmodel::voxelmodel()
{
    //ctor
}

voxelmodel::~voxelmodel()
{
    //dtor
}

void voxelmodel::addpoint(ctilepos tpos, tileid tid)
{
    for (int a = 0; a < 3; a++)
        if (tpos[a] > dims[a]) dims[a] = tpos[a];

    points.emplace_back(point{tpos, tid});
}
