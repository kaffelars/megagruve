#ifndef CHUNKLIGHT_H
#define CHUNKLIGHT_H

#include "chunk.h"

namespace chunklight
{
    void generatelight(chunk& c);
    void updatesunlight(chunk& c, ctilepos ctpos, bool initial);
    void propagateallsunlight(chunk& c);
    void propagatelight(chunk& c, ctilepos ctpos);
    void propagatetilelights(chunk& c);
};

#endif // CHUNKLIGHT_H
