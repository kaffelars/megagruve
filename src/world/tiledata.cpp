#include "consts.h"
#include "tiledata.h"

namespace tiledata
{
    std::vector<tileinfo> tileinfolist;
    bool initialized = false;
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
    tileinfolist.emplace_back(tileinfo{.name="t_air", .fullname="Air block", .ttype = T_EMPTY, .defaultshape = SHAPE_NONE,                  .hardness = 0,  .glow = 0, .needssupport = false, .passable = true, .biometint = false, .breaktexture = "", .sidetextures = {"debug"}});
    tileinfolist.emplace_back(tileinfo{.name="t_water", .fullname="Water block", .ttype = T_WATER, .defaultshape = SHAPE_BLOCK,             .hardness = 0,  .glow = 0, .needssupport = false, .passable = true, .biometint = false, .breaktexture = "water", .sidetextures = {"water"}});
    tileinfolist.emplace_back(tileinfo{.name="t_dirt", .fullname="Dirt block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,               .hardness = 20, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "dirt", .sidetextures = {"dirt"}});
    tileinfolist.emplace_back(tileinfo{.name="t_grass", .fullname="Grass block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,             .hardness = 20, .glow = 0, .needssupport = false, .passable = false, .biometint = true, .breaktexture = "dirt", .sidetextures = {"grassydirt", "grassydirt", "grass", "dirt", "grassydirt", "grassydirt"}});
    tileinfolist.emplace_back(tileinfo{.name="t_grass2", .fullname="Grass block 2", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,          .hardness = 20, .glow = 0, .needssupport = false, .passable = false, .biometint = true, .breaktexture = "dirt", .sidetextures = {"grassydirt", "grassydirt", "grass2", "dirt", "grassydirt", "grassydirt"}});
    tileinfolist.emplace_back(tileinfo{.name="t_snow", .fullname="Snow block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,               .hardness = 20, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "snow", .sidetextures = {"snow"}});
    tileinfolist.emplace_back(tileinfo{.name="t_gravel", .fullname="Gravel block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,           .hardness = 20, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "gravel", .sidetextures = {"gravel"}});
    tileinfolist.emplace_back(tileinfo{.name="t_littlegrass", .fullname="Grass tuft block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,  .hardness = 5,  .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "dirt", .sidetextures = {"dirt", "dirt", "littlegrass", "dirt", "dirt", "dirt"}});
    tileinfolist.emplace_back(tileinfo{.name="t_stone", .fullname="Stone block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,             .hardness = 50, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "stone", .sidetextures = {"stone"}});
    tileinfolist.emplace_back(tileinfo{.name="t_rock", .fullname="Rock block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,               .hardness = 80, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "rock", .sidetextures = {"rock"}});
    tileinfolist.emplace_back(tileinfo{.name="t_ice", .fullname="Ice block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,                 .hardness = 25, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "ice", .sidetextures = {"ice"}});
    tileinfolist.emplace_back(tileinfo{.name="t_sand", .fullname="Sand block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,               .hardness = 5,  .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "sand", .sidetextures = {"sand"}});
    tileinfolist.emplace_back(tileinfo{.name="t_leaves", .fullname="Leaves", .ttype = T_DISCARD, .defaultshape = SHAPE_BLOCK,               .hardness = 2,  .glow = 0, .needssupport = false, .passable = false, .biometint = true, .breaktexture = "green", .sidetextures = {"leaves"}});
    tileinfolist.emplace_back(tileinfo{.name="t_log", .fullname="Tree log", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,                  .hardness = 40, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "log", .sidetextures = {"log", "log", "logtop", "logtop", "log", "log"}});
    tileinfolist.emplace_back(tileinfo{.name="t_planks", .fullname="Planks", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,                 .hardness = 30, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "planks", .sidetextures = {"planks"}});;
    tileinfolist.emplace_back(tileinfo{.name="t_bookcase", .fullname="Bookcase", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,             .hardness = 30, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "planks", .sidetextures = {"bookcase", "bookcase", "planks", "planks", "bookcase", "bookcase"}});;
    tileinfolist.emplace_back(tileinfo{.name="t_flag", .fullname="Decorative flag block", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,    .hardness = 200, .glow = 0, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "flag", .sidetextures = {"flag", "flag", "blue", "blue", "flag", "flag"}});
    tileinfolist.emplace_back(tileinfo{.name="t_grasstuft1", .fullname="Grass tuft 1", .ttype = T_OBJECT, .defaultshape = SHAPE_X,          .hardness = 1,  .glow = 0, .needssupport = true, .passable = true, .biometint = true, .breaktexture = "green", .sidetextures = {"grasstuft1"}});
    tileinfolist.emplace_back(tileinfo{.name="t_grasstuft2", .fullname="Grass tuft 2", .ttype = T_OBJECT, .defaultshape = SHAPE_X,          .hardness = 1,  .glow = 0, .needssupport = true, .passable = true, .biometint = true, .breaktexture = "green", .sidetextures = {"grasstuft2"}});
    tileinfolist.emplace_back(tileinfo{.name="t_cactus", .fullname="Cactus piece", .ttype = T_SOLID_VERT, .defaultshape = SHAPE_CACTUS,     .hardness = 15, .glow = 0, .needssupport = true, .passable = false, .biometint = false, .breaktexture = "green", .sidetextures = {"cactus_side", "cactus_side", "cactus_top", "cactus_top", "cactus_side", "cactus_side"}});
    tileinfolist.emplace_back(tileinfo{.name="t_flower1", .fullname="Yellow flower", .ttype = T_OBJECT, .defaultshape = SHAPE_X,            .hardness = 1,  .glow = 0, .needssupport = true, .passable = true, .biometint = false, .breaktexture = "green", .sidetextures = {"flower1"}});
    tileinfolist.emplace_back(tileinfo{.name="t_flower2", .fullname="Red flower", .ttype = T_OBJECT, .defaultshape = SHAPE_X,               .hardness = 1,  .glow = 0, .needssupport = true, .passable = true, .biometint = false, .breaktexture = "green", .sidetextures = {"flower2"}});
    tileinfolist.emplace_back(tileinfo{.name="t_flower3", .fullname="White flower", .ttype = T_OBJECT, .defaultshape = SHAPE_X,             .hardness = 1,  .glow = 0, .needssupport = true, .passable = true, .biometint = false, .breaktexture = "green", .sidetextures = {"flower3"}});
    tileinfolist.emplace_back(tileinfo{.name="t_glowstone", .fullname="Glowstone", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,           .hardness = 15, .glow = 255, .needssupport = false, .passable = false, .biometint = false, .breaktexture = "green", .sidetextures = {"glowstone"}});

    tileinfolist.emplace_back(tileinfo{.name="t_destroy1", .fullname="cracks", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,               .hardness = 1, .glow = 0, .needssupport = false, .passable = true, .biometint = false, .breaktexture = "", .sidetextures = {"destroy1"}});
    tileinfolist.emplace_back(tileinfo{.name="t_destroy2", .fullname="cracks", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,               .hardness = 1, .glow = 0, .needssupport = false, .passable = true, .biometint = false, .breaktexture = "", .sidetextures = {"destroy2"}});
    tileinfolist.emplace_back(tileinfo{.name="t_destroy3", .fullname="cracks", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,               .hardness = 1, .glow = 0, .needssupport = false, .passable = true, .biometint = false, .breaktexture = "", .sidetextures = {"destroy3"}});
    tileinfolist.emplace_back(tileinfo{.name="t_destroy4", .fullname="cracks", .ttype = T_SOLID, .defaultshape = SHAPE_BLOCK,               .hardness = 1, .glow = 0, .needssupport = false, .passable = true, .biometint = false, .breaktexture = "", .sidetextures = {"destroy4"}});

    for (tileinfo& t : tileinfolist)
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
        texid = 0;
        if (t.breaktexture != "")
        {
            texid = texturemanager::gettiletexturenumber(t.breaktexture);
        }
        t.breaktextureid = texid;
    }

    initializetileshapes();

    initialized = true;
}

uint32_t tiledata::gettileid(std::string tilename)
{
    int index = 0;
    for (tileinfo& t : tileinfolist)
    {
        if (t.name == tilename) return index;
        index++;
    }

    return 0;
}

std::string tiledata::gettilename(tileid tid)
{
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
    return tileinfolist[tile];
}

bool tiledata::isempty(tileid tile)
{
    if (gettileinfo(tile).ttype == T_EMPTY) return true;

    return false;
}

bool tiledata::ispassable(tileid tile)
{
    return gettileinfo(tile).passable;
}

bool tiledata::needssupport(tileid tile)
{
    return gettileinfo(tile).needssupport;
}

bool tiledata::istransparent(tileid tile)
{
    if (gettileinfo(tile).ttype == T_EMPTY || gettileinfo(tile).ttype == T_DISCARD || gettileinfo(tile).ttype == T_TRANSPARENT) return true;

    return false;
}

bool tiledata::isambocc(tileid tile)
{
    if (gettileinfo(tile).defaultshape == SHAPE_BLOCK && gettileinfo(tile).ttype != T_WATER && gettileinfo(tile).glow < 127) return true;
    else return false;
}

tiledata::tiletype tiledata::gettiletype(tileid tile)
{
    return gettileinfo(tile).ttype;
}

tiledata::blockshape tiledata::gettileshape(tileid tile)
{
    return gettileinfo(tile).defaultshape;
}

bool tiledata::renderside(tileid tile, tileid neighbour, uint8_t side)
{
    //yucky
    tiletype ttype = gettiletype(tile);
    tiletype tnb = gettiletype(neighbour);

    switch (ttype)
    {
        case T_SOLID_VERT:
            if (side != 2 && side != 3) return true;
            if (side == 2 || side == 3)
            {
                if (tnb == T_TRANSPARENT || tnb == T_WATER || tnb == T_DISCARD || tnb == T_OBJECT || isempty(neighbour)) return true;
            }
            break;
        case T_SOLID:
            if (tnb == T_TRANSPARENT || tnb == T_WATER || tnb == T_DISCARD || tnb == T_OBJECT || isempty(neighbour) || tnb == T_SOLID_VERT) return true;
            break;
        case T_OBJECT:
            return true;
            break;
        case T_TRANSPARENT:
            if (isempty(neighbour) || tnb == T_WATER || tnb == T_OBJECT || tnb == T_SOLID_VERT || tnb == T_DISCARD) return true;
            break;
        case T_DISCARD:
            if (isempty(neighbour) || tnb == T_WATER || tnb == T_OBJECT || tnb == T_SOLID_VERT) return true;
            break;
        case T_WATER:
            if (isempty(neighbour) || tnb == T_OBJECT || tnb == T_SOLID_VERT || tnb == T_DISCARD || tnb == T_SOLID) return true; //hmm, vann under is?
            break;
    }

    return false;
}
