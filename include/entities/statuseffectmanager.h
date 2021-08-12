#ifndef STATUSEFFECTMANAGER_H
#define STATUSEFFECTMANAGER_H

#include "statuseffect.h"

namespace statuseffectmanager
{
    uint32_t getstatuseffectid(std::string name);
    statuseffect getstatuseffect(std::string name);
    statuseffect createstatuseffect(std::string name, std::string texture, statuseffect s);
    void initialize();
};

#endif // STATUSEFFECTMANAGER_H
