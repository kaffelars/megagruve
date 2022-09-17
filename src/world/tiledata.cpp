#include "consts.h"
#include "tiledata.h"
#include "map_obj_manager.h"

namespace tiledata
{
    std::vector<tileinfo> tileinfolist;
    bool initialized = false;
    tileid firstwaterflowtile;
    tileid watertile;
}

const std::vector<tiledata::tileinfo>& tiledata::gettileinfolist()
{
    return tileinfolist;
}

bool tiledata::isinitialized()
{
    return initialized;
}

void tiledata::initialize()
{
    //hent fra fil elns
    tileinfolist.emplace_back(tileinfo{.name="t_air", .fullname="Air block", .ttype = T_EMPTY, .defaultshape = SHAPE_NONE, .lightattenuation = 0,                   .hardness = 0,  .glow = 0, .needssupport = false, .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "", .sidetextures = {"debug"}});
    tileinfolist.emplace_back(tileinfo{.name="t_water", .fullname="Water source block", .ttype = T_WATER, .defaultshape = SHAPE_WATER, .lightattenuation = 2,             .hardness = 0,  .glow = 0, .needssupport = false, .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "water", .sidetextures = {"water_side","water_side","water","water","water_side","water_side"}});
    tileinfolist.emplace_back(tileinfo{.name="t_dirt", .fullname="Dirt block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,              .hardness = 20, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "dirt", .sidetextures = {"dirt"}});
    tileinfolist.emplace_back(tileinfo{.name="t_lava", .fullname="Lava block", .ttype = T_LAVA, .defaultshape = SHAPE_BLOCK, .lightattenuation = 0,                 .hardness = 0,  .glow = 15,.needssupport = false,.overbuildable = true,  .passable = true, .biometint = false, .breaktexture = "lava", .sidetextures = {"lava"}});
    tileinfolist.emplace_back(tileinfo{.name="t_grass", .fullname="Grass block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,            .hardness = 20, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = true, .breaktexture = "dirt", .sidetextures = {"dirt", "dirt", "grass", "dirt", "dirt", "dirt"}, .overlaytextures = {"grass_side_overlay", "grass_side_overlay", "", "", "grass_side_overlay", "grass_side_overlay"}});
    tileinfolist.emplace_back(tileinfo{.name="t_grass2", .fullname="Grass block 2", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,         .hardness = 20, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = true, .breaktexture = "dirt", .sidetextures = {"dirt", "dirt", "grass2", "dirt", "dirt", "dirt"}, .overlaytextures = {"grass_side_overlay", "grass_side_overlay", "", "", "grass_side_overlay", "grass_side_overlay"}});
    tileinfolist.emplace_back(tileinfo{.name="t_mossydirt", .fullname="Mossy dirt block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,   .hardness = 20, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = true, .breaktexture = "dirt", .sidetextures = {"dirt"}, .overlaytextures = {"leaves", "leaves", "leaves", "leaves", "leaves", "leaves"}});
    tileinfolist.emplace_back(tileinfo{.name="t_snow", .fullname="Snow block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,              .hardness = 20, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "snow", .sidetextures = {"snow"}});
    tileinfolist.emplace_back(tileinfo{.name="t_gravel", .fullname="Gravel block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,          .hardness = 20, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "gravel", .sidetextures = {"gravel"}});
    tileinfolist.emplace_back(tileinfo{.name="t_littlegrass", .fullname="Grass tuft block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15, .hardness = 5,  .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "dirt", .sidetextures = {"dirt", "dirt", "littlegrass", "dirt", "dirt", "dirt"}});
    tileinfolist.emplace_back(tileinfo{.name="t_stone", .fullname="Stone block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,            .hardness = 50, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "stone", .sidetextures = {"stone"}});
    tileinfolist.emplace_back(tileinfo{.name="t_rock", .fullname="Rock block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,              .hardness = 80, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "rock", .sidetextures = {"rock"}});
    tileinfolist.emplace_back(tileinfo{.name="t_white_tiles", .fullname="White tile block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15, .hardness = 40, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "white_tiles", .sidetextures = {"white_tiles"}});
    tileinfolist.emplace_back(tileinfo{.name="t_bricks", .fullname="Bricks", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,                .hardness = 40, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "brick", .sidetextures = {"brick"}});
    tileinfolist.emplace_back(tileinfo{.name="t_hayblock", .fullname="Block of hay", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,        .hardness = 5, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "hay_block_top", .sidetextures = {"hay_block_side", "hay_block_side", "hay_block_top", "hay_block_top", "hay_block_side", "hay_block_side"}});
    tileinfolist.emplace_back(tileinfo{.name="t_coalore", .fullname="Coal ore block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,       .hardness = 100, .glow = 0, .needssupport = false,.overbuildable = false,  .passable = false, .biometint = false, .breaktexture = "rock", .sidetextures = {"coal_ore"}});
    tileinfolist.emplace_back(tileinfo{.name="t_ironore", .fullname="Iron ore block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,       .hardness = 120, .glow = 0, .needssupport = false,.overbuildable = false,  .passable = false, .biometint = false, .breaktexture = "rock", .sidetextures = {"iron_ore"}});
    tileinfolist.emplace_back(tileinfo{.name="t_diamondore", .fullname="Diamond ore block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15, .hardness = 180, .glow = 0, .needssupport = false,.overbuildable = false,  .passable = false, .biometint = false, .breaktexture = "rock", .sidetextures = {"diamond_ore"}});
    tileinfolist.emplace_back(tileinfo{.name="t_ice", .fullname="Ice block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 6,                 .hardness = 25, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "ice", .sidetextures = {"ice"}});
    tileinfolist.emplace_back(tileinfo{.name="t_sand", .fullname="Sand block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,              .hardness = 5,  .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "sand", .sidetextures = {"sand"}});
    tileinfolist.emplace_back(tileinfo{.name="t_sandstone_block", .fullname="Sandstone block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,.lightattenuation = 15,.hardness = 35, .glow = 0, .needssupport = false,.overbuildable = false,  .passable = false, .biometint = false, .breaktexture = "sandstone_block", .sidetextures = {"sandstone_block"}});
    tileinfolist.emplace_back(tileinfo{.name="t_glass", .fullname="Glass block", .ttype = T_DISCARD, .defaultshape = SHAPE_BLOCK,.lightattenuation = 0,.hardness = 10, .glow = 0, .needssupport = false,.overbuildable = false,  .passable = false, .biometint = false, .breaktexture = "glass", .sidetextures = {"glass"}});
    tileinfolist.emplace_back(tileinfo{.name="t_window", .fullname="Window block", .ttype = T_DISCARD, .defaultshape = SHAPE_BLOCK,.lightattenuation = 0,.hardness = 10, .glow = 0, .needssupport = false,.overbuildable = false,  .passable = false, .biometint = false, .breaktexture = "glass", .sidetextures = {"window"}});
    tileinfolist.emplace_back(tileinfo{.name="t_clay", .fullname="Clay block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,              .hardness = 5,  .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "clay", .sidetextures = {"clay"}});
    tileinfolist.emplace_back(tileinfo{.name="t_leaves", .fullname="Leaves", .ttype = T_DISCARD, .defaultshape = SHAPE_BLOCK, .lightattenuation = 1,               .hardness = 2,  .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = true, .breaktexture = "green", .sidetextures = {"leaves"}});
    tileinfolist.emplace_back(tileinfo{.name="t_log", .fullname="Tree log", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,                 .hardness = 40, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "log", .sidetextures = {"log", "log", "logtop", "logtop", "log", "log"}});
    tileinfolist.emplace_back(tileinfo{.name="t_birch_log", .fullname="Birch tree log", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,     .hardness = 40, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "log", .sidetextures = {"log_birch", "log_birch", "log_birch_top", "log_birch_top", "log_birch", "log_birch"}});
    tileinfolist.emplace_back(tileinfo{.name="t_planks", .fullname="Planks", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,                .hardness = 30, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "planks", .sidetextures = {"planks"}});;
    tileinfolist.emplace_back(tileinfo{.name="t_bookcase", .fullname="Bookcase", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,            .hardness = 30, .glow = 0, .needssupport = false, .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "planks", .sidetextures = {"bookcase", "bookcase", "planks", "planks", "bookcase", "bookcase"}});;
    tileinfolist.emplace_back(tileinfo{.name="t_flag", .fullname="Decorative flag block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,   .hardness = 200, .glow = 0, .needssupport = false,.overbuildable = false,  .passable = false, .biometint = false, .breaktexture = "flag", .sidetextures = {"flag", "flag", "blue", "blue", "flag", "flag"}});
    tileinfolist.emplace_back(tileinfo{.name="t_grasstuft1", .fullname="Grass tuft 1", .ttype = T_OBJECT, .defaultshape = SHAPE_X, .lightattenuation = 0,           .hardness = 1,  .glow = 0, .needssupport = true,  .overbuildable = true, .passable = true, .biometint = true, .breaktexture = "green", .sidetextures = {"grasstuft1"}});
    tileinfolist.emplace_back(tileinfo{.name="t_grasstuft2", .fullname="Grass tuft 2", .ttype = T_OBJECT, .defaultshape = SHAPE_X, .lightattenuation = 0,           .hardness = 1,  .glow = 0, .needssupport = true,  .overbuildable = true, .passable = true, .biometint = true, .breaktexture = "green", .sidetextures = {"grasstuft2"}});
    tileinfolist.emplace_back(tileinfo{.name="t_grass_bottom", .fullname="Grass bottom", .ttype = T_OBJECT, .defaultshape = SHAPE_X, .lightattenuation = 0,         .hardness = 1,  .glow = 0, .needssupport = true,  .overbuildable = true, .passable = true, .biometint = true, .breaktexture = "green", .sidetextures = {"grass_bottom"}});
    tileinfolist.emplace_back(tileinfo{.name="t_grass_top", .fullname="Grass top", .ttype = T_OBJECT, .defaultshape = SHAPE_X, .lightattenuation = 0,               .hardness = 1,  .glow = 0, .needssupport = true,  .overbuildable = true, .passable = true, .biometint = true, .breaktexture = "green", .sidetextures = {"grass_top"}});
    tileinfolist.emplace_back(tileinfo{.name="t_cactus", .fullname="Cactus piece", .ttype = T_SOLID_VERT, .defaultshape = SHAPE_CACTUS, .lightattenuation = 15,    .hardness = 15, .glow = 0, .needssupport = true,  .overbuildable = false, .passable = false, .biometint = false, .breaktexture = "green", .sidetextures = {"cactus_side", "cactus_side", "cactus_top", "cactus_top", "cactus_side", "cactus_side"}});
    tileinfolist.emplace_back(tileinfo{.name="t_flower1", .fullname="Yellow flower", .ttype = T_OBJECT, .defaultshape = SHAPE_X, .lightattenuation = 0,             .hardness = 1,  .glow = 0, .needssupport = true,  .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "green", .sidetextures = {"flower1"}});
    tileinfolist.emplace_back(tileinfo{.name="t_flower2", .fullname="Red flower", .ttype = T_OBJECT, .defaultshape = SHAPE_X, .lightattenuation = 0,                .hardness = 1,  .glow = 0, .needssupport = true,  .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "green", .sidetextures = {"flower2"}});
    tileinfolist.emplace_back(tileinfo{.name="t_flower3", .fullname="White flower", .ttype = T_OBJECT, .defaultshape = SHAPE_X, .lightattenuation = 0,              .hardness = 1,  .glow = 0, .needssupport = true,  .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "green", .sidetextures = {"flower3"}});
    tileinfolist.emplace_back(tileinfo{.name="t_glowstone", .fullname="Glowstone", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,          .hardness = 15, .glow = 15, .needssupport = false,.overbuildable = false,  .passable = false, .biometint = false, .breaktexture = "green", .sidetextures = {"glowstone"}});
    tileinfolist.emplace_back(tileinfo{.name="t_bedrock", .fullname="Bedrock block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 15,        .hardness = 255, .glow = 0, .needssupport = false,.overbuildable = false,  .passable = false, .biometint = false, .breaktexture = "bedrock", .sidetextures = {"bedrock"}});

    tileinfolist.emplace_back(tileinfo{.name="t_waterflow1", .fullname="Full water flow block", .ttype = T_WATER, .defaultshape = SHAPE_WATER, .lightattenuation = 2,             .hardness = 0,  .glow = 0, .needssupport = false, .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "water", .sidetextures = {"water_side","water_side","water","water","water_side","water_side"}});
    tileinfolist.emplace_back(tileinfo{.name="t_waterflow2", .fullname="5/6 water flow block", .ttype = T_WATER, .defaultshape = SHAPE_WATER, .lightattenuation = 2,             .hardness = 0,  .glow = 0, .needssupport = false, .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "water", .sidetextures = {"water_side","water_side","water","water","water_side","water_side"}});
    tileinfolist.emplace_back(tileinfo{.name="t_waterflow3", .fullname="4/6 water flow block", .ttype = T_WATER, .defaultshape = SHAPE_WATER, .lightattenuation = 2,             .hardness = 0,  .glow = 0, .needssupport = false, .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "water", .sidetextures = {"water_side","water_side","water","water","water_side","water_side"}});
    tileinfolist.emplace_back(tileinfo{.name="t_waterflow4", .fullname="3/6 water flow block", .ttype = T_WATER, .defaultshape = SHAPE_WATER, .lightattenuation = 2,             .hardness = 0,  .glow = 0, .needssupport = false, .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "water", .sidetextures = {"water_side","water_side","water","water","water_side","water_side"}});
    tileinfolist.emplace_back(tileinfo{.name="t_waterflow5", .fullname="2/6 water flow block", .ttype = T_WATER, .defaultshape = SHAPE_WATER, .lightattenuation = 2,             .hardness = 0,  .glow = 0, .needssupport = false, .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "water", .sidetextures = {"water_side","water_side","water","water","water_side","water_side"}});
    tileinfolist.emplace_back(tileinfo{.name="t_waterflow6", .fullname="1/6 water flow block", .ttype = T_WATER, .defaultshape = SHAPE_WATER, .lightattenuation = 2,             .hardness = 0,  .glow = 0, .needssupport = false, .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "water", .sidetextures = {"water_side","water_side","water","water","water_side","water_side"}});

    tileinfolist.emplace_back(tileinfo{.name="t_destroy1", .fullname="cracks", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 0,              .hardness = 1, .glow = 0, .needssupport = false, .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "", .sidetextures = {"destroy1"}});
    tileinfolist.emplace_back(tileinfo{.name="t_destroy2", .fullname="cracks", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 0,              .hardness = 1, .glow = 0, .needssupport = false, .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "", .sidetextures = {"destroy2"}});
    tileinfolist.emplace_back(tileinfo{.name="t_destroy3", .fullname="cracks", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 0,              .hardness = 1, .glow = 0, .needssupport = false,  .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "", .sidetextures = {"destroy3"}});
    tileinfolist.emplace_back(tileinfo{.name="t_destroy4", .fullname="cracks", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK, .lightattenuation = 0,              .hardness = 1, .glow = 0, .needssupport = false, .overbuildable = true, .passable = true, .biometint = false, .breaktexture = "", .sidetextures = {"destroy4"}});

    finalizetileinfos(tileinfolist);

    firstwaterflowtile = gettileid("t_waterflow1");
    watertile = gettileid("t_water");

    initializetileshapes();

    map_obj_manager::initialize();

    initialized = true;
}

void tiledata::finalizetileinfos(std::vector<tileinfo>& data)
{
    for (tileinfo& t : data)
    {
        int index = 0;
        int texid = 0;
        for (std::string& s:t.sidetextures)
        {
            if (s != "")
            {
                texid = texturemanager::gettiletexturenumber(s);
            }
            t.sidetextureids[index] = texid;
            index++;
        }
        //texid = 0; //breaktexture = default side texture hvis ikke specified
        if (t.breaktexture != "")
        {
            texid = texturemanager::gettiletexturenumber(t.breaktexture);
        }
        t.breaktextureid = texid;

        index = 0;

        for (std::string& s:t.overlaytextures)
        {
            texid = 0;
            if (s != "")
            {
                texid = texturemanager::gettiletexturenumber(s);
            }
            t.overlaytextureids[index] = texid;
            index++;
        }
    }
}

tileid tiledata::gettileid(std::string tilename)
{
    tileid index = 0;
    for (tileinfo& t : tileinfolist)
    {
        if (t.name == tilename) return index;
        index++;
    }

    return 0;
}

std::string tiledata::gettilename(tileid tid)
{
    if (tid == 255) return "map obj";

    if (tid >= 0 && tid < tileinfolist.size())
        return tileinfolist[tid].name;
    else
        return "no tile";
}

/*tiledata::tileinfo& tiledata::gettileinfo(uint32_t id)
{
    return tileinfolist[id];
}*/

inline tiledata::tileinfo& tiledata::gettileinfo(tileid tile)
{
    if (tile == 255)
    {
        return tileinfolist[0];//map_obj_manager::getmapobjinfo(0); //hmmmmm
    }
    return tileinfolist[tile];
}

bool tiledata::isempty(tileid tile)
{
    if (tile == 255) return false;
    if (gettileinfo(tile).ttype == T_EMPTY) return true;

    return false;
}

bool tiledata::ispassable(tileid tile)
{
    if (tile == 255)
    {
        return false;//map_obj_manager::getmapobjinfo(0).passable;//hmm
    }
    return gettileinfo(tile).passable;
}

bool tiledata::needssupport(tileid tile)
{
    if (tile == 255)
    {
        return map_obj_manager::getmapobjinfo(0).needssupport;
    }
    return gettileinfo(tile).needssupport;
}

bool tiledata::isoverbuildable(tileid tile)
{
    if (tile == 255)
    {
        return false;//map_obj_manager::getmapobjinfo(0).needssupport;
    }
    return gettileinfo(tile).overbuildable;
}

bool tiledata::istransparent(tileid tile)
{
    if (tile == 255) return true;
    if (gettileinfo(tile).ttype == T_EMPTY || gettileinfo(tile).ttype == T_DISCARD || gettileinfo(tile).ttype == T_TRANSPARENT) return true;

    return false;
}

bool tiledata::iswater(tileid tile)
{
    return (gettileinfo(tile).ttype == T_WATER);
}

bool tiledata::isflowingwater(tileid tile)
{
    return (tile > watertile && gettileinfo(tile).ttype == T_WATER);
}

float tiledata::getwaterheight(tileid tile)
{
    if (iswater(tile))
    {
        if (tile != watertile)
        {
            return (0.15f * (1 + tile - firstwaterflowtile));
        }

        return 0.1f;
    }

    return 1.0f;
}

bool tiledata::isglow(tileid tile)
{
    return (gettileinfo(tile).glow > 0); //check for 255 is in gettileinfo
}

uint8_t tiledata::getglow(tileid tile)
{
    return gettileinfo(tile).glow;
}

bool tiledata::isambocc(tileid tile)
{
    if (tile == 255) return false;
    if (gettileinfo(tile).defaultshape == SHAPE_BLOCK && gettileinfo(tile).glow < 127) return true;
    else return false;
}

tiledata::tiletype tiledata::gettiletype(tileid tile)
{
    if (tile == 255) return T_MAP_OBJ;
    return gettileinfo(tile).ttype;
}

tiledata::blockshape tiledata::gettileshape(tileid tile)
{
    if (tile == 255) return SHAPE_CUSTOM;
    return gettileinfo(tile).defaultshape;
}

bool tiledata::renderside(tileid tile, tileid neighbour, uint8_t side)
{
    if (tile == 255 || neighbour == 255) return true;
    //yucky
    tiletype ttype = gettiletype(tile);
    tiletype tnb = gettiletype(neighbour);

    switch (ttype)
    {
        case T_SOLID_VERT:
            if (side != 2 && side != 3) return true;
            if (side == 2 || side == 3)
            {
                if (tnb == T_TRANSPARENT || tnb == T_WATER || tnb == T_DISCARD || tnb == T_OBJECT || tnb == T_LAVA || isempty(neighbour)) return true;
            }
            break;
        case T_SOLID:
            if (tnb == T_TRANSPARENT || tnb == T_WATER || tnb == T_DISCARD || tnb == T_OBJECT || isempty(neighbour) || tnb == T_LAVA || tnb == T_SOLID_VERT) return true;
            break;
        case T_OBJECT:
            return true;
            break;
        case T_TRANSPARENT:
            if (isempty(neighbour) || tnb == T_WATER || tnb == T_OBJECT || tnb == T_SOLID_VERT || tnb == T_LAVA || tnb == T_DISCARD) return true;
            break;
        case T_DISCARD:
            if (isempty(neighbour) || tnb == T_WATER || tnb == T_OBJECT || tnb == T_LAVA || tnb == T_SOLID_VERT) return true;
            break;
        case T_WATER:
            if (isempty(neighbour) || tnb == T_OBJECT || tnb == T_SOLID_VERT || tnb == T_DISCARD || tnb == T_LAVA) return true;// || tnb == T_SOLID) return true; //hmm, vann under is?
            break;
        case T_LAVA:
            if (isempty(neighbour) || tnb == T_OBJECT || tnb == T_SOLID_VERT || tnb == T_DISCARD || tnb == T_WATER) return true;// || tnb == T_SOLID) return true;
            break;
        case T_EMPTY:
            return false;
            break;
        case T_MAP_OBJ:
            return false;
            break;
    }

    return false;
}
