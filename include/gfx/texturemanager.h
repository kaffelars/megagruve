#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "settings.h"

namespace texturemanager
{
    enum iconsizes
    {
        ICONS_SMALL, ICONS_MEDIUM, ICONS_LARGE //10x10, 16x16, 24x24
    };

    struct tiletexture
    {
        std::string name;
    };

    void initialize();

    void bindtiletextures(int texid=0);
    void bindcloudtexture(int texid=0);
    void bindiconstexture(iconsizes iconsize, int texid=0);

    void getbiometint(std::vector<rgbcolor255>& rgb);

    uint32_t gettiletexturenumber(std::string texturename);
    uint32_t geticontexturenumber(std::string texturename, iconsizes iconsize);
    uint32_t gettiletexturefromitemtexture(uint32_t itemtexid);
};

#endif // TEXTUREMANAGER_H
