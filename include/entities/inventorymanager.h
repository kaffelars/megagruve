#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include "inventory.h"

namespace inventorymanager
{
    void swaporcombine(inventory& inv1, int32_t invslot1, inventory& inv2, int32_t invslot2);
    void movehalfstack(inventory& inv1, int32_t invslot1, inventory& inv2, int32_t invslot2);
    void swapitems(inventory& inv1, int32_t invslot1, inventory& inv2, int32_t invslot2);
    bool moveonlyone(inventory& inv1, int32_t invslot1, inventory& inv2, int32_t invslot2);
    bool movealltoinv2(inventory& inv1, int32_t invslot1, inventory& inv2);
    void sortinv(inventory& inv);
    void movewholeinv(inventory& invfrom, inventory& invto, int excludeupto = 0);
    void sorttoinv(inventory& invfrom, inventory& invto, int excludeupto);
};

#endif // INVENTORYMANAGER_H
