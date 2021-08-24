#ifndef BIOMECONTROLLER_H
#define BIOMECONTROLLER_H


#include "chunk.h"
#include "tiledata.h"

namespace biomecontroller
{

    void initialize();
    rgbcolor255 getbiometint(chunk::biomedata b);

};

#endif // BIOMECONTROLLER_H
