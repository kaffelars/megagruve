#ifndef MAINCHARCONTROLLER_H
#define MAINCHARCONTROLLER_H


#include "inventory.h"

namespace maincharcontroller
{
    enum smode
    {
        SEL_BLOCK, SEL_AIR, SEL_NONE
    };

    direction getviewdir();
    hdirection gethviewdir();
    wposition getmaincharposition();
    void updatecamera();
    void movement();
    void toggleflying();
    void inputactions();
    wtilepos gettilehover();
    void initialize();
    void renderselection();
    void setselectionmode(smode selmode);

    int32_t getactionbarselection();
    int32_t getcurrenthealth();
    int32_t getmaxhealth();

    inventory& getmcharinventory();



    smode getselectionmode();
};

#endif // MAINCHARCONTROLLER_H
