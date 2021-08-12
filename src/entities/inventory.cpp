#include "consts.h"
#include "inventory.h"

#include "itemmanager.h"

inventory::inventory(int32_t invsiz)
{
    invsize = invsiz;
    resizeinv(invsize);

    emptyinvitem.itemid = 0;
    emptyinvitem.quantity = 0;
}

inventory::~inventory()
{
    //dtor
}

inventory::invitem& inventory::getinvitem(uint32_t position)
{
    if (position >= 0 && position < invitems.size())
    {
        return invitems[position];
    }
    else
    {
        return emptyinvitem;
    }
}

void inventory::resizeinv(uint32_t newsize)
{
    uint32_t oldsize = invitems.size();

    if (newsize > oldsize) //enlarge inv
    {
        for (int a = oldsize; a < newsize; a++)
        {
            invitems.emplace_back(invitem{.itemid = 0, .quantity = 0});
        }
    }
}

bool inventory::additem(invitem itemtoadd) //returner overskuddsitems hvis f.eks. en halv stack får plass istedenfor bool
{
    bool itemadded = false;
    int index = 0;
    for (invitem& i : invitems)
    {
        if (i.quantity == 0) //empty slot
        {
            i = itemtoadd;
            itemadded = true;
            break;
        }
        index++;
    }

    return itemadded;
}

bool inventory::additem(std::string itemid, uint32_t quantity)
{
    int32_t itemidnum = itemmanager::getitemid(itemid);
    return additem(invitem{itemidnum, quantity});
}
