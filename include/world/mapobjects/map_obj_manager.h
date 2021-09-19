#ifndef MAP_OBJ_MANAGER_H
#define MAP_OBJ_MANAGER_H

#include "chunk.h"
#include "tiledata.h"

namespace map_obj_manager
{

    struct mapobjinfo
    {
        std::string name;
        std::string fullname;
        std::string description;
        mapobjplacement placement;
        uint8_t hardness;
        uint8_t glow;
        bool needssupport;
        std::string breaktexture;
        uint32_t breaktextureid;
        std::string icontexture {""};
        uint32_t icontextureid {0};
    };


    void addmapobj(chunk& c, ctilepos ctpos, uint8_t mapobjid, uint8_t forwardside);

    uint8_t getfacingside();

    void initialize();

    mapobjinfo& getmapobjinfo(uint32_t id);

    std::vector<mapobjinfo>& getmapobjlist();
    std::vector<ctilepos>& getmapobjchildren(uint8_t mapobjid);
};

#endif // MAP_OBJ_MANAGER_H
