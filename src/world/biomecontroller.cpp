#include "consts.h"

#include "biomecontroller.h"
#include "texturemanager.h"
#include "chunkcoords.h"

namespace biomecontroller
{


    std::vector<rgbcolor255> biometintcolors;
}

void biomecontroller::initialize()
{
    texturemanager::getbiometint(biometintcolors);
}

rgbcolor255 biomecontroller::getbiometint(chunk::biomedata b)
{
    return biometintcolors[b.temperature + 256 * (b.humidity)];
}


