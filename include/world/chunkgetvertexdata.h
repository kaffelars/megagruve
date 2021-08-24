#ifndef CHUNKGETVERTEXDATA_H
#define CHUNKGETVERTEXDATA_H

#include "chunk.h"
#include "tiledata.h"

namespace chunkgetvertexdata
{
    void setambocc(chunk& c, ctilepos tilepos, tiledata::tilesides ts, uint8_t (&ambocc)[4]);
    void setsunlight(chunk& c, ctilepos tilepos, tiledata::tilesides ts, uint8_t (&sunlight)[4]);
    void getbiometintvertexes(chunk& c, chtilepos ctpos, tiledata::tilesides ts, rgbcolor255 (&rgb)[4]);
};

#endif // CHUNKGETVERTEXDATA_H
