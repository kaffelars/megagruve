#include "consts.h"
#include "map_obj_manager.h"

#include "texturemanager.h"

#include "obj_chest.h"
#include "obj_flagpole.h"
#include "obj_ctable.h"
#include "obj_door.h"
#include "obj_child.h"
#include "obj_button.h"
#include "obj_lightbulb.h"

namespace map_obj_manager
{
    std::vector<mapobjinfo> mapobjectsinfo;
    std::vector<std::vector<ctilepos>> mapobjchildren;
}

void map_obj_manager::initialize()
{
    mapobjectsinfo.emplace_back(mapobjinfo{.name="o_chest", .fullname="Chest", .description = "Use to store items", .placement = mapobjplacement::ground, .hardness = 100, .glow = 0, .needssupport = false, .breaktexture = "planks", .icontexture = "chest_front"});
    mapobjchildren.push_back(std::vector<ctilepos> {});
    mapobjectsinfo.emplace_back(mapobjinfo{.name="o_flagpole", .fullname="Flagpole", .description = "Select flag and right click to hoist flag",  .placement = mapobjplacement::ground, .hardness = 150, .glow = 0, .needssupport = true, .breaktexture = "flagpole", .icontexture = "flagpole"});
    mapobjchildren.push_back(std::vector<ctilepos> {});
    mapobjectsinfo.emplace_back(mapobjinfo{.name="o_ctable", .fullname="Crafting table", .description = "Craft items and stuff", .placement = mapobjplacement::ground, .hardness = 100, .glow = 0, .needssupport = true, .breaktexture = "planks", .icontexture = "crafting_table"});
    mapobjchildren.push_back(std::vector<ctilepos> {});
    mapobjectsinfo.emplace_back(mapobjinfo{.name="o_door", .fullname="Door", .description = "Can be opened and closed", .placement = mapobjplacement::ground, .hardness = 100, .glow = 0, .needssupport = true, .breaktexture = "planks", .icontexture = "door_upper"});
    mapobjchildren.push_back(std::vector<ctilepos> {ctilepos{0,-1,0}});
    mapobjectsinfo.emplace_back(mapobjinfo{.name="o_button", .fullname="Button", .description = "Activates nearby doors etc. when right-clicked", .placement = mapobjplacement::verticalsurface, .hardness = 100, .glow = 0, .needssupport = true, .breaktexture = "planks", .icontexture = "button"});
    mapobjchildren.push_back(std::vector<ctilepos> {});
    mapobjectsinfo.emplace_back(mapobjinfo{.name="o_lightbulb", .fullname="Lightbulb", .description = "Emits a pleasant light", .placement = mapobjplacement::surface, .hardness = 100, .glow = 255, .needssupport = true, .breaktexture = "lightbulb", .icontexture = "lightbulb"});
    mapobjchildren.push_back(std::vector<ctilepos> {});

    /*mapobjectsinfo.emplace_back(tiledata::tileinfo{.name="o_chest", .fullname="Chest", .ttype = tiledata::T_SOLID, .defaultshape = tiledata::SHAPE_BLOCK,               .hardness = 100, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "planks", .sidetextures = {"chest_front"}});
    mapobjchildren.push_back(std::vector<ctilepos> {});
    mapobjectsinfo.emplace_back(tiledata::tileinfo{.name="o_flagpole", .fullname="Flagpole", .ttype = tiledata::T_SOLID, .defaultshape = tiledata::SHAPE_BLOCK,               .hardness = 150, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "flagpole", .sidetextures = {"flagpole"}});
    mapobjchildren.push_back(std::vector<ctilepos> {});
    mapobjectsinfo.emplace_back(tiledata::tileinfo{.name="o_ctable", .fullname="Crafting table", .ttype = tiledata::T_SOLID, .defaultshape = tiledata::SHAPE_BLOCK,               .hardness = 100, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "planks", .sidetextures = {"crafting_table"}});
    mapobjchildren.push_back(std::vector<ctilepos> {});
    mapobjectsinfo.emplace_back(tiledata::tileinfo{.name="o_door", .fullname="Door", .ttype = tiledata::T_SOLID, .defaultshape = tiledata::SHAPE_BLOCK,               .hardness = 100, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "planks", .sidetextures = {"door_upper"}});
    mapobjchildren.push_back(std::vector<ctilepos> {ctilepos{0,-1,0}});
    mapobjectsinfo.emplace_back(tiledata::tileinfo{.name="o_button", .fullname="Button", .ttype = tiledata::T_SOLID, .defaultshape = tiledata::SHAPE_BLOCK,               .hardness = 100, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "planks", .sidetextures = {"button"}});
    mapobjchildren.push_back(std::vector<ctilepos> {});*/

    for (mapobjinfo& t : mapobjectsinfo)
    {
        int texid = 0;

        t.icontextureid = texturemanager::gettiletexturenumber(t.icontexture);

        if (t.breaktexture != "")
        {
            texid = texturemanager::gettiletexturenumber(t.breaktexture);
        }
        t.breaktextureid = texid;
    }
}

uint32_t map_obj_manager::getmapobjid(std::string mapobjname)
{
    int index = 0;
    for (mapobjinfo& m : mapobjectsinfo)
    {
        if (m.name == mapobjname) return index;
        index++;
    }

    return 0;
}

std::vector<map_obj_manager::mapobjinfo>& map_obj_manager::getmapobjlist()
{
    return mapobjectsinfo;
}

std::vector<ctilepos>& map_obj_manager::getmapobjchildren(uint8_t mapobjid)
{
    return mapobjchildren[mapobjid];
}


void map_obj_manager::addmapobj(chunk& c, ctilepos ctpos, uint8_t mapobjid, uint8_t forwardside)
{
    c.settile(ctpos, 255);
    std::shared_ptr<map_obj> objecttoadd;
    //std::shared_ptr<map_obj> obj = std::make_shared<obj_chest> (ctpos, c.cpos, 0);
    switch (mapobjid)
    {
    case 0:
        objecttoadd = std::make_shared<obj_chest> (ctpos, c.cpos, forwardside, 30);
        break;
    case 1:
        objecttoadd = std::make_shared<obj_flagpole> (ctpos, c.cpos, forwardside);
        break;
    case 2:
        objecttoadd = std::make_shared<obj_ctable> (ctpos, c.cpos, forwardside);
        break;
    case 3:
        objecttoadd = std::make_shared<obj_door> (ctpos, c.cpos, forwardside);
        break;
    case 4:
        objecttoadd = std::make_shared<obj_button> (ctpos, c.cpos, forwardside);
        break;
    case 5:
        objecttoadd = std::make_shared<obj_lightbulb> (ctpos, c.cpos, forwardside);
        break;
    }

    objecttoadd->mapobjid = mapobjid;

    objecttoadd->create();

    c.chunk_objs.emplace(c.get3dcoord(ctpos), objecttoadd);

    for (ctilepos& ct : mapobjchildren[mapobjid])
    {
        ctilepos childpos = ctpos + ct;
        c.settile(childpos, 255);
        c.chunk_objs.emplace(c.get3dcoord(childpos), std::make_shared<obj_child> (childpos, c.cpos, objecttoadd));
    }
}

uint8_t map_obj_manager::getfacingside()
{
    return 0;
}

map_obj_manager::mapobjinfo& map_obj_manager::getmapobjinfo(uint32_t id)
{
    return mapobjectsinfo[id];
}
