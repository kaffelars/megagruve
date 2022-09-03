#ifndef CHESTINVENTORYFILLER_H
#define CHESTINVENTORYFILLER_H

#include "chunk.h"

namespace chestinventoryfiller
{
    void initialize();
    void addfilledchest(chunk& c, ctilepos tpos, uint8_t forwardside, int32_t chestfillid);
};

#endif // CHESTINVENTORYFILLER_H
