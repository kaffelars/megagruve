#include "consts.h"
#include "map_obj_manager.h"

#include "texturemanager.h"

#include "obj_chest.h"
#include "obj_flagpole.h"
#include "obj_ctable.h"

namespace map_obj_manager
{
    std::vector<tiledata::tileinfo> mapobjectsinfo;
}

void map_obj_manager::initialize()
{
    mapobjectsinfo.emplace_back(tiledata::tileinfo{.name="o_chest", .fullname="Chest", .ttype = tiledata::T_SOLID, .defaultshape = tiledata::SHAPE_BLOCK,               .hardness = 100, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "planks", .sidetextures = {"chest_front"}});
    mapobjectsinfo.emplace_back(tiledata::tileinfo{.name="o_flagpole", .fullname="Flagpole", .ttype = tiledata::T_SOLID, .defaultshape = tiledata::SHAPE_BLOCK,               .hardness = 150, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "flagpole", .sidetextures = {"flagpole"}});
    mapobjectsinfo.emplace_back(tiledata::tileinfo{.name="o_ctable", .fullname="Crafting table", .ttype = tiledata::T_SOLID, .defaultshape = tiledata::SHAPE_BLOCK,               .hardness = 100, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "planks", .sidetextures = {"crafting_table"}});

    tiledata::finalizetileinfos(mapobjectsinfo);
}

std::vector<tiledata::tileinfo>& map_obj_manager::getmapobjlist()
{
    return mapobjectsinfo;
}


void map_obj_manager::addmapobj(chunk& c, ctilepos ctpos, uint8_t mapobjid, uint8_t forwardside)
{
    c.settile(ctpos, 255);
    //std::shared_ptr<map_obj> obj = std::make_shared<obj_chest> (ctpos, c.cpos, 0);
    switch (mapobjid)
    {
    case 0:
        c.chunk_objs.emplace(c.get3dcoord(ctpos), std::make_shared<obj_chest> (ctpos, c.cpos, forwardside));
        break;
    case 1:
        c.chunk_objs.emplace(c.get3dcoord(ctpos), std::make_shared<obj_flagpole> (ctpos, c.cpos, forwardside));
        break;
    case 2:
        c.chunk_objs.emplace(c.get3dcoord(ctpos), std::make_shared<obj_ctable> (ctpos, c.cpos, forwardside));
        break;
    }
}

uint8_t map_obj_manager::getfacingside()
{
    return 0;
}

tiledata::tileinfo& map_obj_manager::getmapobjinfo(uint32_t id)
{
    return mapobjectsinfo[id];
}
