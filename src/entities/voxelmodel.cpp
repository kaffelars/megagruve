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

void voxelmodel::centermodel()
{
    for (point& p: points)
    {
        p.tilepos.x -= centerbottomtile.x;
        p.tilepos.z -= centerbottomtile.z;
    }
    dims[0] -= centerbottomtile.x;
    dims[2] -= centerbottomtile.z;
    centerbottomtile.x = 0;
    centerbottomtile.z = 0;
}
