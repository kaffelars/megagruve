#include "consts.h"
#include "chestinventoryfiller.h"
#include "inventory.h"

#include "map_obj_manager.h"
#include "obj_chest.h"
#include "map_obj.h"
#include "itemmanager.h"
#include "randfunc.h"

namespace chestinventoryfiller
{
    uint32_t chestobjid;

    void fillinventory(inventory& i, wtilepos position, int32_t fillid);
}

void chestinventoryfiller::initialize()
{
    chestobjid = map_obj_manager::getmapobjid("o_chest");
}

void chestinventoryfiller::addfilledchest(chunk& c, ctilepos tpos, uint8_t forwardside, int32_t chestfillid)
{
    c.addchunkobj(tpos, chestobjid, forwardside);

    std::shared_ptr<obj_chest> chest = std::dynamic_pointer_cast<obj_chest>(c.chunk_objs.at(c.get3dcoord(tpos)));

    fillinventory(chest->chestinv, wtilepos(c.cpos.x * chunkwidth + tpos.x, tpos.y, c.cpos.y * chunkwidth + tpos.z), chestfillid);
}

void chestinventoryfiller::fillinventory(inventory& i, wtilepos pos, int32_t fillid)
{
    i.clearinventory();

    if (fillid == 1) //standard village chest
    {
        int appleid = itemmanager::getitemid("i_apple");
        int fireballid = itemmanager::getitemid("i_fireball");
        int breadid = itemmanager::getitemid("i_bread");
        int potatoid = itemmanager::getitemid("i_potato");

        for (int a = 0; a < static_cast<int>(i.getinvsize()); a++)
        {
            float randnum = randfunc::noise(pos.x+193*a, pos.y+191*a, 0.13f);

            if (randnum > 0.5f)
            {
                inventory::invitem it;
                if (randnum > 0.98f)
                {
                    it.itemid = fireballid;
                }
                else if (randnum > 0.9f)
                {
                    it.itemid = breadid;
                }
                else if (randnum > 0.7f)
                {
                    it.itemid = appleid;
                }
                else
                {
                    it.itemid = potatoid;
                }

                float randnum2 = randfunc::noise(pos.x-37*a, pos.y-21*a, 0.13f) + 1.0f;
                it.quantity = (int(randnum2)*3) + 1;

                i.setinvitem(a, it);
            }
        }
    }

    if (fillid == 2) //random ingots or coal
    {
        int itemid;

        float randnum = randfunc::noise(pos.x-193, pos.y-191, 0.13f);

        if (randnum > 0.0f)
            itemid = itemmanager::getitemid("i_coal");
        else if (randnum > -0.5f)
            itemid = itemmanager::getitemid("i_ironingot");
        else
            itemid = itemmanager::getitemid("i_goldingot");

        for (int a = 0; a < static_cast<int>(i.getinvsize()); a++)
        {
            float randnum2 = randfunc::noise(pos.x-23*a, pos.y+21*a, 0.13f);

            if (randnum2 > 0.7f)
            {
                inventory::invitem it;
                it.itemid = itemid;
                it.quantity = randnum2 * 3 + 1;

                i.setinvitem(a, it);
            }
        }
    }
}
