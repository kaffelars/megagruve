#ifndef CHUNKGETVERTEXDATA_H
#define CHUNKGETVERTEXDATA_H

#include "chunk.h"
#include "tiledata.h"

namespace chunkgetvertexdata
{
    void setambocc(chunk& c, ctilepos tilepos, tiledata::tilesides ts, uint8_t (&ambocc)[4]);
    uint8_t getambocc(chunk& c, ctilepos vertex);
    void setsunlight(chunk& c, ctilepos tilepos, tiledata::tilesides ts, uint8_t (&sunlight)[4]);
    void getbiometintvertexes(chunk& c, ctilepos ctpos, tiledata::tilesides ts, rgbcolor255 (&rgb)[4]);
    void getbiometintvertex(chunk& c, ctilepos vertexpos, rgbcolor255& rgb);
    void setwatercornersheight(chunk& c, ctilepos middletile, float (&corners)[4]);
};

#endif // CHUNKGETVERTEXDATA_H
