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

void voxelmodel::addmapobject(ctilepos tpos, uint8_t mapobjid, uint8_t forwardside, int32_t extrainfo)
{
    for (int a = 0; a < 3; a++)
        if (tpos[a] > dims[a]) dims[a] = tpos[a];

    mapobjects.emplace_back(mapobject{tpos, mapobjid, forwardside, extrainfo});
}

void voxelmodel::centermodel()
{
    for (point& p: points)
    {
        p.tilepos.x -= centerbottomtile.x;
        p.tilepos.z -= centerbottomtile.z;
    }

    for (mapobject& m: mapobjects)
    {
        m.tilepos.x -= centerbottomtile.x;
        m.tilepos.z -= centerbottomtile.z;
    }

    dims[0] -= centerbottomtile.x;
    dims[2] -= centerbottomtile.z;
    centerbottomtile.x = 0;
    centerbottomtile.z = 0;
}
