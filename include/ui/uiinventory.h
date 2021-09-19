#ifndef UIINVENTORY_H
#define UIINVENTORY_H

#include "inventory.h"

namespace uiinventory
{
    void updatescale();
    void updateinvslots();
    void updategridgfx(bool alsobg);
    void renderinventory();
    void initialize();
    void click(int8_t clicktype);
    bool inventoryitemsupdated();
    void setextrainventory(inventory& inv);
    void showinventory(inventorytype itype);
};

#endif // UIINVENTORY_H
