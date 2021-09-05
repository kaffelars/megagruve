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

void inventory::swapitems(int32_t position1, int32_t position2)
{
    if (positionininv(position1) && positionininv(position2))
    {
        invitem i1 = getinvitem(position1);
        invitem i2 = getinvitem(position2);

        setinvitem(position1, i2);
        setinvitem(position2, i1);
    }
}

void inventory::swaporcombineitems(int32_t position1, int32_t position2)
{
    if (positionininv(position1) && positionininv(position2))
    {
        invitem i1 = getinvitem(position1);
        invitem i2 = getinvitem(position2);

        if (i1.itemid != i2.itemid)
        {
            swapitems(position1, position2);
        }
        else
        {
            itemmanager::item& item = itemmanager::getitem(i2.itemid);

            if (i2.quantity >= item.maxstack)
            {
                swapitems(position1, position2);
            }
            else
            {
                i2.quantity += i1.quantity;
                if (i2.quantity > item.maxstack)
                {
                    i1.quantity = i2.quantity-item.maxstack;
                    i2.quantity = item.maxstack;
                }
                else
                    i1.quantity = 0;

                setinvitem(position1, i1);
                setinvitem(position2, i2);
            }
        }
    }
}

inventory::invitem& inventory::getinvitem(int32_t position)
{
    if (positionininv(position))
    {
        return invitems[position];
    }
    else
    {
        return emptyinvitem;
    }
}

bool inventory::positionininv(int32_t position)
{
    if (position >= 0 && position < invitems.size())
        return true;
    return false;
}

void inventory::setinvitem(int32_t position, invitem item)
{
    if (positionininv(position))
        invitems[position] = item;
}

inventory::invitem& inventory::removeinvitem(int32_t position)
{
    if (position >= 0 && position < invitems.size())
    {
        invitem i = invitems[position];
        invitems[position].quantity = 0;
        return i;
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

uint32_t inventory::getinvsize()
{
    return invsize;
}

bool inventory::additem(invitem itemtoadd) //returner overskuddsitems hvis f.eks. en halv stack får plass istedenfor bool
{
    bool itemadded = false;
    int index = 0;
    //sjekk om den kan adderes først
    for (invitem& i : invitems)
    {
        if (i.itemid == itemtoadd.itemid)
        {
            itemmanager::item& item = itemmanager::getitem(i.itemid);
            if (i.quantity < item.maxstack)
            {
                i.quantity += itemtoadd.quantity;
                itemtoadd.quantity = 0;
                if (i.quantity > item.maxstack) {
                    itemtoadd.quantity = i.quantity - item.maxstack;
                    i.quantity = item.maxstack;
                }
            }
        }
    }

    if (itemtoadd.quantity > 0) //hvis noe er igjen, putt evt. resten i empty slot
    {
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
    }

    return itemadded;
}

bool inventory::additem(std::string itemid, uint32_t quantity)
{
    int32_t itemidnum = itemmanager::getitemid(itemid);
    return additem(invitem{itemidnum, quantity});
}
