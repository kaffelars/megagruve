
enum class itemtype
{
    block, tool, usable, consumable, inert, equipment, placeableobject, flag, none
};

enum class itemsubtype
{
    helmet, chest, boots, trinket, other, none
};

enum class s_effect
{
    poison, heal
};

enum class selectionmode
{
    block, air, noselection
};

enum class boundingboxtype
{
    point, line, box
};

enum class statid
{
    maxhp, attack, defense, movespeed, usespeed
};

enum class iconsize
{
    small, medium, large //10x10, 16x16, 24x24
};

enum class movementmode
{
    sneaking=0, walking=1, running=2//flying etc
};

enum class sceneid
{
    mainmenu, settings, ingame, blank
};

enum class shaderid
{
    main, scene, sky, postprocessing, line, icons, water, particle, bob
};

enum class settingid
{
    screenx, screeny, fov, chunkdist, antialias, tileresolution, vsync, uiscale, language, mbox, maxthreads, bbox
};

enum class chunktag
{
    start, generating, generated, meshing, meshed, ready, remeshing, remeshed
};

enum class tiletype
{
    emptytile, transparent, discard, solid, solid_vert, water, object, mapobject
};

enum class blockshape
{
    block, x, cactus, stairs, slab, water, noshape, custom
};

enum class tilesideflag
{
    xm = 1, xp = 2, ym = 4, yp = 8, zm = 16, zp = 32
};

enum class tilesideid
{
    xm = 0, xp = 1, ym = 2, yp = 3, zm = 4, zp = 5, noside = 6
};

enum class mapobjplacement
{
    ground, surface, verticalsurface, horizontalsurface
};

enum class inventorytype
{
    none, chest, craftingtable
};
