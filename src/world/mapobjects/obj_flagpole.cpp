#include "consts.h"
#include "obj_flagpole.h"

#include "map_obj_models.h"
#include "itemmanager.h"
#include "inventory.h"
#include "texturemanager.h"

obj_flagpole::~obj_flagpole()
{
    //dtor
}

obj_flagpole::obj_flagpole(ctilepos ctp, chunkpos cpo, uint8_t forw) : map_obj(ctp, cpo, forw)
{
    hasmodel = true;
}

void obj_flagpole::addmodel(ctilepos ctp, chunkmesh& cmesh, chunklightcontainer& sunlight)
{
    //tiledata::addblock(ctp, 2, 0, 255, 255, notint, 0, 0, notint, cmesh);
    map_obj_models::addmodel(cmesh, sunlight, ctp, 2, forwardside);

    if (flagtextureid >= 0)
        map_obj_models::addmodel(cmesh, sunlight, ctp, 3, forwardside, flagtextureid);
}

void obj_flagpole::interact(mainchar& interactor)
{
    //lidopen = !lidopen;
    if (flagtextureid >= 0)
    {
        inventory::invitem flag;
        flag.itemid = flagitemid;
        flag.quantity = 1;
        interactor.additem(flag);
        flagtextureid = -1;
        flagitemid = -1;
    }
    else
    {
        inventory::invitem& iitem = interactor.mcharinv.getinvitem(interactor.actionbarselection);

        if (interactor.getitemusecooldown(interactor.actionbarselection) == 0 && iitem.quantity > 0)
        {
            itemmanager::item& iteminfo = itemmanager::getitem(iitem.itemid);
            if (iteminfo.itemtype == itemtype::flag)
            {
                flagitemid = iitem.itemid;
                flagtextureid = texturemanager::gettiletexturefromitemtexture(iteminfo.textureid);
                interactor.usecurrentlyselecteditem(true);
            }
        }

    }
    remeshchunk();
}

void obj_flagpole::destroy()
{
    //husk å fixe remove map_obj fra chunk
}

uint8_t obj_flagpole::lightattenuation()
{
    return 0;
}
