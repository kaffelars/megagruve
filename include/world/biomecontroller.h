#ifndef BIOMECONTROLLER_H
#define BIOMECONTROLLER_H


#include "chunk.h"
#include "tiledata.h"

namespace biomecontroller
{

    void initialize();
    rgbcolor255 getbiometint(chunk::biomedata b);
    void getbiometintvertexes(chunk& c, chtilepos ctpos, tiledata::tilesides ts, rgbcolor255 (&rgb)[4]);
};

#endif // BIOMECONTROLLER_H
