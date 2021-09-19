#include "consts.h"
#include "inventorymanager.h"
#include "itemmanager.h"

namespace inventorymanager
{

}

bool inventorymanager::moveonlyone(inventory& inv1, int32_t invslot1, inventory& inv2, int32_t invslot2)
{
    inventory::invitem i1 = inv1.getinvitem(invslot1);
    inventory::invitem i2 = inv2.getinvitem(invslot2);

    if (i2.quantity > 0 && i1.itemid != i2.itemid) return false;

    itemmanager::item& item = itemmanager::getitem(i2.itemid);

    if (i2.quantity >= item.maxstack) return false;

    i1.quantity -= 1;
    i2.quantity += 1;

    i2.itemid = i1.itemid;

    inv1.setinvitem(invslot1, i1);
    inv2.setinvitem(invslot2, i2);

    if (i1.quantity == 0) return true;
    else return false;
}

void inventorymanager::movehalfstack(inventory& inv1, int32_t invslot1, inventory& inv2, int32_t invslot2)
{
    inventory::invitem i1 = inv1.getinvitem(invslot1);
    inventory::invitem i2 = inv2.getinvitem(invslot2);

    if (i2.quantity > 0) return; //må være empty

    int32_t q1 = i1.quantity;

    i1.quantity /= 2;

    i2.itemid = i1.itemid;
    i2.quantity = q1 - i1.quantity;

    inv1.setinvitem(invslot1, i1);
    inv2.setinvitem(invslot2, i2);
}

void inventorymanager::swaporcombine(inventory& inv1, int32_t invslot1, inventory& inv2, int32_t invslot2)
{
    inventory::invitem i1 = inv1.getinvitem(invslot1);
    inventory::invitem i2 = inv2.getinvitem(invslot2);

    if (i2.quantity <= 0)
    {
        inv2.setinvitem(invslot2, i1);
        inv1.removeinvitem(invslot1);
    }
    else
    {
        if (i2.itemid != i1.itemid) //swap
        {
            swapitems(inv1, invslot1, inv2, invslot2);
        }
        else
        {
            itemmanager::item& item = itemmanager::getitem(i2.itemid);

            if (i2.quantity >= item.maxstack)
            {
                swapitems(inv1, invslot1, inv2, invslot2);
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

                inv1.setinvitem(invslot1, i1);
                inv2.setinvitem(invslot2, i2);
            }
        }
    }
}

void inventorymanager::swapitems(inventory& inv1, int32_t invslot1, inventory& inv2, int32_t invslot2)
{
    inventory::invitem i1 = inv1.getinvitem(invslot1);
    inventory::invitem i2 = inv2.getinvitem(invslot2);

    inv1.setinvitem(invslot1, i2);
    inv2.setinvitem(invslot2, i1);
}
