#include "consts.h"
#include "chunkdecorator.h"
#include "voxelmodel.h"
#include "voxelmodels.h"
#include "chunkcoords.h"

namespace chunkdecorator
{
    //ctor
}

void chunkdecorator::addvoxelmodel(chunk& c, ctilepos ctpos, uint32_t voxelmodelid, bool cgenerator, bool overwrite)
{
    voxelmodel& v = voxelmodels::getvoxelmodel(voxelmodelid);

    ctilepos offset = ctilepos(
                               ctpos.x - (v.centerbottomtile.x),
                               ctpos.y - v.centerbottomtile.y-1,
                               ctpos.z - (v.centerbottomtile.z)
                               );

    for (voxelmodel::point& vp : v.points)
    {
        ctilepos cpos = ctilepos(offset.x + vp.tilepos.x, offset.y + vp.tilepos.y, offset.z + vp.tilepos.z);
        if (chunkcoords::withinextendedchunkbounds(cpos))
        {
            tileid t = c.gettile(cpos);
            if (t == 0 || overwrite)
            {
                c.settile(cpos, vp.tid);
            }
        }
    }
}
