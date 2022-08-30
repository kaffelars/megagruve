#include "consts.h"
#include "chunkdecorator.h"
#include "voxelmodel.h"
#include "voxelmodels.h"
#include "chunkcoords.h"

namespace chunkdecorator
{
    //ctor
}

void chunkdecorator::addvoxelmodel(chunk& c, ctilepos ctpos, uint32_t voxelmodelid, bool cgenerator, bool overwrite, uint8_t rotation) //rotate center bottom tile?
{
    voxelmodel& v = voxelmodels::getvoxelmodel(voxelmodelid);

    ctilepos centerbottom = v.centerbottomtile;

    ctilepos offset = ctilepos(
                               ctpos.x - (centerbottom.x),
                               ctpos.y - centerbottom.y-1,
                               ctpos.z - (centerbottom.z)
                               );

    for (voxelmodel::point& vp : v.points)
    {
        ctilepos vctpos=ctilepos(offset.x + vp.tilepos.x, offset.y + vp.tilepos.y, offset.z + vp.tilepos.z);
        switch (rotation)
        {
            case 0: vctpos=ctilepos(offset.x + vp.tilepos.x, offset.y + vp.tilepos.y, offset.z + vp.tilepos.z);break;
            case 1: vctpos = ctilepos(offset.x + vp.tilepos.z, offset.y + vp.tilepos.y, offset.z + vp.tilepos.x);break;
            case 2: vctpos=ctilepos(offset.x - vp.tilepos.x, offset.y + vp.tilepos.y, offset.z - vp.tilepos.z);break;
            case 3: vctpos = ctilepos(offset.x - vp.tilepos.z, offset.y + vp.tilepos.y, offset.z - vp.tilepos.x);break;
            default:break;
        }
        if (chunkcoords::withinextendedchunkbounds(vctpos))
        {
            tileid t = c.gettile(vctpos);
            if (t == 0 || overwrite)
            {
                c.settile(vctpos, vp.tid);
            }
        }
        if (!chunkcoords::withinchunkbounds(vctpos))
        {
            chunkpos cps = chunkpos{0,0};
            if (vctpos.x <= 0) {cps.x=-1; vctpos.x += chunkwidth;}
            else if (vctpos.x >= chunkwidth-1) {cps.x=1; vctpos.x -= chunkwidth;}
            if (vctpos.z <= 0) {cps.y=-1; vctpos.z += chunkwidth;}
            else if (vctpos.z >= chunkwidth-1) {cps.y=1; vctpos.z -= chunkwidth;}

            c.addoutsidetiles(cps, vctpos, vp.tid);
        }
    }
}

uint32_t chunkdecorator::getvoxelmodelid(std::string voxelmodelname)
{
    return voxelmodels::getvoxelmodelid(voxelmodelname);
}
