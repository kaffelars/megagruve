#ifndef CHUNKLIGHT_H
#define CHUNKLIGHT_H

#include "chunk.h"

namespace chunklight
{
    void generatesunlight(chunk& c);
    void updatesunlight(chunk& c, ctilepos ctpos, bool initial);
    void propagateallsunlight(chunk& c);
};

#endif // CHUNKLIGHT_H
