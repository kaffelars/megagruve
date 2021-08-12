#ifndef ESCBOX_H
#define ESCBOX_H

#include "uielement.h"
#include "scenec.h"

namespace escbox
{
    enum class selection
    {
        BACK, SETTINGS, MENU, QUIT, NONE
    };

    selection showescbox();
};

#endif // ESCBOX_H
