#ifndef CHUNKCOORDS_H
#define CHUNKCOORDS_H

#include "tiledata.h"

namespace chunkcoords
{
    chunkpos wpostocpos(wposition wpos);
    chunkpos wtilepostocpos(wtilepos wtpos);
    ctilepos wpostoctilepos(wposition wpos);
    wtilepos wpostowtilepos(wposition wpos);
    ctilepos wtilepostoctilepos(wtilepos wtpos);
    wposition cpostowpos(chunkpos cpos);
    bool wtileposwithinworldbounds(wtilepos wtpos);
    wtilepos cposctilepostowtilepos(chunkpos cpos, ctilepos ctpos);
    void getvertexoffset(tiledata::tilesides ts, chtilepos (&around)[4]);
    void getvertexoffset(tiledata::tilesides ts, ctilepos (&around)[4]);

    void getabovetiles(tiledata::tilesides ts, ctilepos (&above)[4]);

    bool withinchunkbounds(ctilepos cpos);
    bool withinextendedchunkbounds(ctilepos cpos);
}



#endif
