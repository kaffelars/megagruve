#ifndef UIICONS_H
#define UIICONS_H

#include "vaocontainer.h"

namespace uiicons
{
    void initialize();
    void additemicon(vaocontainer& vaoc, float xpos, float ypos, uint32_t textureid, uint32_t quantity, float iconsize);
};

#endif // UIICONS_H
