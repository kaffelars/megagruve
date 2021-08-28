#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "physicsobject.h"

namespace physicsmanager
{
    void dophysics(physicsobject& p);
    void pointphysics(physicsobject& p); //exposed i tilfelle man vil gunne på med den direkte
    void boxphysics(physicsobject& p);
};

#endif // PHYSICSMANAGER_H
