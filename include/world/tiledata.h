#ifndef TILEDATA_H
#define TILEDATA_H

#include "tileshape.h"
#include "chunkmesh.h"
#include "texturemanager.h"

namespace tiledata
{
    enum tiletype
    {
        T_EMPTY, T_TRANSPARENT, T_DISCARD, T_SOLID, T_SOLID_VERT, T_WATER, T_LAVA, T_OBJECT, T_MAP_OBJ
    };

    enum blockshape
    {
        SHAPE_BLOCK, SHAPE_X, SHAPE_CACTUS, SHAPE_STAIRS, SHAPE_SLAB, SHAPE_WATER, SHAPE_NONE, SHAPE_CUSTOM
    };

    enum tilesides
    {
        SIDE_XM = 1, SIDE_XP = 2, SIDE_YM = 4, SIDE_YP = 8, SIDE_ZM = 16, SIDE_ZP = 32
    };

    const tilesides sideflags[6] = {SIDE_XM, SIDE_XP, SIDE_YM, SIDE_YP, SIDE_ZM, SIDE_ZP};
    const tilesides oppositesideflags[6] = {SIDE_XP, SIDE_XM, SIDE_YP, SIDE_YM, SIDE_ZP, SIDE_ZM};

    struct tileinfo
    {
        std::string name;
        std::string fullname;
        tiletype ttype;
        blockshape defaultshape;
        uint8_t lightattenuation;
        uint8_t hardness;
        uint8_t glow;
        bool needssupport;
        bool passable;
        bool biometint;
        std::string breaktexture;
        uint32_t breaktextureid;
        std::string sidetextures[6] {"", "", "", "", "", ""};
        uint32_t sidetextureids[6] {0,0,0,0,0,0};
        std::string overlaytextures[6] {"", "", "", "", "", ""};
        uint32_t overlaytextureids[6] {0,0,0,0,0,0};
    };

    void initializetileshapes();
    void addblock(ctilepos cpos, tileid id, uint32_t bshape, uint8_t tilesides, uint8_t sunlight, rgbcolor255 light, uint8_t glow, uint8_t ambocc, rgbcolor255 tint, chunkmesh& cmesh);
    void addside(ctilepos cpos, tileid id, uint32_t bshape, uint8_t tileside, uint8_t sunlight[4], rgbcolor255 light[4], uint8_t glow, uint8_t ambocc[4], rgbcolor255 tint[4], chunkmesh& cmesh, bool overlay = false);

    uint32_t gettileid(std::string tilename);
    //tileinfo& gettileinfo(uint32_t id);
    tiletype gettiletype(tileid tile);
    blockshape gettileshape(tileid tile);

    bool isinitialized();

    std::string gettilename(tileid tid);
    const std::vector<tileinfo>& gettileinfolist();

    inline tileinfo& gettileinfo(tileid tile);

    bool isempty(tileid tile);
    bool istransparent(tileid tile);
    bool isambocc(tileid tile);
    bool needssupport(tileid tile);
    bool ispassable(tileid tile);

    void initialize();
    void finalizetileinfos(std::vector<tileinfo>& data);

    bool renderside(tileid tile, tileid neighbour, uint8_t side); //true hvis side på 'tile' skal rendes mot 'neighbour'
};

#endif // TILEDATA_H
