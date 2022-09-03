#include "consts.h"
#include "chunkdecorator.h"
#include "voxelmodel.h"
#include "voxelmodels.h"
#include "chunkcoords.h"
#include "chestinventoryfiller.h"
#include "map_obj_manager.h"

namespace chunkdecorator
{
    //ctor
}

void chunkdecorator::addvoxelmodel(chunk& c, ctilepos ctpos, uint32_t voxelmodelid, bool cgenerator, bool overwrite, uint8_t forwardside) //rotate center bottom tile?
{
    voxelmodel& v = voxelmodels::getvoxelmodel(voxelmodelid);

    ctilepos centerbottom = v.centerbottomtile;

    //hax
    if (forwardside == 2) forwardside = 4;
    if (forwardside == 3) forwardside = 5;

    ctilepos offset = ctilepos(
                               ctpos.x - (centerbottom.x),
                               ctpos.y - centerbottom.y-1,
                               ctpos.z - (centerbottom.z)
                               );

    for (const voxelmodel::point& vp : v.points)
    {
        ctilepos vctpos=ctilepos(offset.x + vp.tilepos.x, offset.y + vp.tilepos.y, offset.z + vp.tilepos.z);
        switch (forwardside)
        {
            case 0: vctpos=ctilepos(offset.x + vp.tilepos.x, offset.y + vp.tilepos.y, offset.z + vp.tilepos.z);break; //x- default
            case 1: vctpos=ctilepos(offset.x - vp.tilepos.x, offset.y + vp.tilepos.y, offset.z - vp.tilepos.z);break; //x+
            case 4: vctpos = ctilepos(offset.x + vp.tilepos.z, offset.y + vp.tilepos.y, offset.z + vp.tilepos.x);break; //z-
            case 5: vctpos = ctilepos(offset.x - vp.tilepos.z, offset.y + vp.tilepos.y, offset.z - vp.tilepos.x);break; //z+
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

    for (const voxelmodel::mapobject& m: v.mapobjects)
    {
        ctilepos vctpos=ctilepos(offset.x + m.tilepos.x, offset.y + m.tilepos.y, offset.z + m.tilepos.z);
        switch (forwardside)
        {
            case 0: vctpos=ctilepos(offset.x + m.tilepos.x, offset.y + m.tilepos.y, offset.z + m.tilepos.z);break; //x- default
            case 1: vctpos=ctilepos(offset.x - m.tilepos.x, offset.y + m.tilepos.y, offset.z - m.tilepos.z);break; //x+
            case 4: vctpos = ctilepos(offset.x + m.tilepos.z, offset.y + m.tilepos.y, offset.z + m.tilepos.x);break; //z-
            case 5: vctpos = ctilepos(offset.x - m.tilepos.z, offset.y + m.tilepos.y, offset.z - m.tilepos.x);break; //z+
            default:break;
        }
        //rotate forwardside - messy
        uint8_t fforward = m.forwardside;
        if (forwardside != 0 && m.forwardside != 2 && m.forwardside != 3) //not rotate when facing y
        {
            if (m.forwardside == 0)
            {
                fforward = forwardside;
            }
            else if (m.forwardside == 1)
            {
                switch (forwardside)
                {
                    case 1: fforward = 0;break;
                    case 4: fforward = 5;break;
                    case 5: fforward = 4;break;
                    default:break;
                }
            }
            else if (m.forwardside == 4)
            {
                switch (forwardside)
                {
                    case 1: fforward = 5;break;
                    case 4: fforward = 1;break;
                    case 5: fforward = 0;break;
                    default:break;
                }
            }
            else if (m.forwardside == 5)
            {
                switch (forwardside)
                {
                    case 1: fforward = 4;break;
                    case 4: fforward = 0;break;
                    case 5: fforward = 1;break;
                    default:break;
                }
            }
        }

        if (chunkcoords::withinchunkbounds(vctpos))
        {
            if (m.extrainfo > 0 && m.mapobjid == map_obj_manager::getmapobjid("o_chest"))
                chestinventoryfiller::addfilledchest(c, vctpos, fforward, m.extrainfo);
            else
                c.addchunkobj(vctpos, m.mapobjid, fforward);
        }
    }
}

uint32_t chunkdecorator::getvoxelmodelid(std::string voxelmodelname)
{
    return voxelmodels::getvoxelmodelid(voxelmodelname);
}
