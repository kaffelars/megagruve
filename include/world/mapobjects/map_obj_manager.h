#ifndef MAP_OBJ_MANAGER_H
#define MAP_OBJ_MANAGER_H

#include "chunk.h"
#include "tiledata.h"

namespace map_obj_manager
{
    void addmapobj(chunk& c, ctilepos ctpos, uint8_t mapobjid, uint8_t forwardside);

    uint8_t getfacingside();

    void initialize();

    tiledata::tileinfo& getmapobjinfo(uint32_t id);

    std::vector<tiledata::tileinfo>& getmapobjlist();
    std::vector<ctilepos>& getmapobjchildren(uint8_t mapobjid);
};

#endif // MAP_OBJ_MANAGER_H
