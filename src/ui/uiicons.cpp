#include "consts.h"
#include "uiicons.h"

#include "texturemanager.h"

namespace uiicons
{
    std::vector<uint32_t> numbertotexid;
}

void uiicons::initialize()
{
    for (int a = 0; a < 10; a++)
    {
        uint32_t texid = texturemanager::geticontexturenumber(std::to_string(a), texturemanager::ICONS_MEDIUM);
        numbertotexid.push_back(texid);
    }
}

void uiicons::additemicon(vaocontainer& vaoc, float xpos, float ypos, uint32_t textureid, uint32_t quantity, float iconsize)
{
    vaoc.addvalues(0, xpos, ypos, textureid, iconsize);
    if (quantity > 1)
    {
        int8_t digits[3] {-1, -1, -1};
        digits[2] = quantity % 10;
        if (quantity > 9)
        {
            digits[1] = (quantity / 10) %10;
        }
        if (quantity > 99) {
            digits[0] = (quantity / 100) %10;
        }

        float numbericonsize = iconsize / 3.0f;

        for (int a = 0; a < 3; a++)
        {
            if (digits[a] != -1)
                vaoc.addvalues(0, (xpos+numbericonsize*(a-1)), ypos+numbericonsize*1.1f, numbertotexid[digits[a]], numbericonsize);
        }
    }
}
