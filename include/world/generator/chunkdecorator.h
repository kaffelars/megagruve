#ifndef CHUNKDECORATOR_H
#define CHUNKDECORATOR_H

#include "chunk.h"

namespace chunkdecorator
{
    void addvoxelmodel(chunk& c, ctilepos ctpos, uint32_t voxelmodelid, bool cgenerator, bool overwrite = false);
};

#endif // CHUNKDECORATOR_H
