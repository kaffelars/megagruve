#include "consts.h"
#include "scenegamehelperfunctions.h"

#include "inputmanager.h"
#include "uiingame.h"
#include "uiinventory.h"
#include "maincharcontroller.h"
#include "inputmanager.h"

namespace scenegamehelperfunctions
{
    scenegame* sgame;
}

void scenegamehelperfunctions::setscenepointer(scenegame* sg)
{
    sgame = sg;
}

void scenegamehelperfunctions::toggleinventory(inventorytype invtype)
{
    sgame->showinginventory = !sgame->showinginventory;

    if (sgame->showinginventory)
    {
        inputmanager::pausekeyfunctionsexcept(std::vector<inputmanager::keys_enum> {inputmanager::KEY_SELECT, inputmanager::KEY_ESCAPE, inputmanager::KEY_INV, inputmanager::KEY_INTERACT});
        inputmanager::setkeyfunction(inputmanager::KEY_SELECT, [&](){uiinventory::click(0);}, inputmanager::KE_CLICKED);
        inputmanager::setkeyfunction(inputmanager::KEY_INTERACT, [&](){uiinventory::click(1);}, inputmanager::KE_CLICKED);
        inputmanager::setkeyfunction(inputmanager::KEY_SELECT, [&](){}, inputmanager::KE_HELD);
        uiingame::toggleinventory(invtype);
        maincharcontroller::setmaincharcameramoveable(false);
        inputmanager::showmouse();
    }
    else
    {
        sgame->setkeys();
        inputmanager::resumeallkeyfunctions();
        maincharcontroller::setmaincharcameramoveable(true);
        uiingame::toggleinventory();
        inputmanager::hidemouse();
        //inputmanager::resumekeyfunctions();
    }
}
