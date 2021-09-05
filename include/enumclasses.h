
enum class itemtype
{
    I_BLOCK, I_DIG, I_USABLE, I_CONSUMABLE, I_INERT, I_PLACEABLEOBJECT, I_FLAG
};

enum class s_effect
{
    SE_POISON, SE_HEAL
};

enum class selectionmode
{
    SEL_BLOCK, SEL_AIR, SEL_NONE
};

enum class boundingboxtype
{
    BB_POINT, BB_LINE, BB_BOX
};

enum class statid
{
    STAT_MAXHP, STAT_ATTACK, STAT_DEFENSE, STAT_MOVESPEED, STAT_USESPEED
};

enum class iconsize
{
    ICONS_SMALL, ICONS_MEDIUM, ICONS_LARGE //10x10, 16x16, 24x24
};

enum class sceneid
{
    S_MAINMENU, S_SETTINGS, S_GAME, S_BLANK
};

enum class shaderid
{
    SH_MAIN, SH_SCENE, SH_SKY, SH_PP, SH_LINE, SH_ICONS, SH_WATER, SH_PARTICLE, SH_BOB
};

enum class settingid
{
    SET_SCREENX, SET_SCREENY, SET_FOV, SET_CDIST, SET_AA, SET_TILERES, SET_VSYNC, SET_UISCALE, SET_LANGUAGE, SET_MBOX, SET_MAXTHREADS, SET_BBOX
};

enum class chunktag
{
    C_START, C_GENERATING, C_GENERATED, C_MESHING, C_MESHED, C_READY, C_REMESHING, C_REMESHED
};

enum class tiletype
{
    T_EMPTY, T_TRANSPARENT, T_DISCARD, T_SOLID, T_SOLID_VERT, T_WATER, T_OBJECT, T_MAP_OBJ
};

enum class blockshape
{
    SHAPE_BLOCK, SHAPE_X, SHAPE_CACTUS, SHAPE_STAIRS, SHAPE_SLAB, SHAPE_WATER, SHAPE_NONE, SHAPE_CUSTOM
};

enum class tilesideflag
{
    SIDE_XM = 1, SIDE_XP = 2, SIDE_YM = 4, SIDE_YP = 8, SIDE_ZM = 16, SIDE_ZP = 32
};

enum class tilesideid
{
    SIDE_XM = 0, SIDE_XP = 1, SIDE_YM = 2, SIDE_YP = 3, SIDE_ZM = 4, SIDE_ZP = 5, SIDE_NONE = 6
};
