#include "consts.h"
#include "itemmanager.h"

namespace itemmanager
{
    std::vector<item> items;

    std::unordered_map<std::string, uint32_t> itemnametoid;

    void additem(std::string itemid, item itemtoadd);
}

void itemmanager::additem(std::string itemname, std::string texturename, item itemtoadd)
{
    uint32_t textureid = texturemanager::geticontexturenumber(texturename, texturemanager::ICONS_MEDIUM);
    itemtoadd.textureid = textureid;


    itemtoadd.selectionmode = maincharcontroller::SEL_NONE;
    if (itemtoadd.itemtype == I_DIG)
        itemtoadd.selectionmode = maincharcontroller::SEL_BLOCK;
    if (itemtoadd.itemtype == I_BLOCK || itemtoadd.itemtype == I_PLACEABLEOBJECT)
        itemtoadd.selectionmode = maincharcontroller::SEL_AIR;

    items.emplace_back(itemtoadd);

    uint32_t id = items.size()-1;
    itemnametoid.insert(std::make_pair(itemname, id));
}

itemmanager::item& itemmanager::getitem(uint32_t itemnumid)
{
    return items[itemnumid];
}

uint32_t itemmanager::getitemid(std::string itemname)
{
    if (itemnametoid.find(itemname) == itemnametoid.end()) return 0;

    return itemnametoid.at(itemname);
}

void itemmanager::initialize()
{
    //hent fra fil
    /*additem("i_debug", "debug", item{.name="Error item", .description="An error has occurred", .speed=5, .duration=5, .maxstack=1, .itemtype=I_INERT, .useeffects=std::vector<effect*>{}});
    additem("i_ironpickaxe", "iron_pickaxe", item{.name="Iron Pickaxe", .description="A pickaxe made from iron", .speed=5, .duration=5, .maxstack=1, .itemtype=I_TOOL, .useeffects=std::vector<effect*>{new attackeffect(8, 1)}});
    additem("i_ironaxe", "iron_axe", item{.name="Iron Axe", .description="An axe made from iron", .speed=7, .duration=5, .maxstack=1, .itemtype=I_TOOL, .useeffects=std::vector<effect*>{new attackeffect(10, 2)}});
    additem("i_apple", "apple", item{.name="Red apple", .description="Delicious red apple", .speed=5, .duration=0, .maxstack=10, .itemtype=I_USABLE, .useeffects=std::vector<effect*>{new healeffect(1)}});*/

    additem("i_debug", "debug", item{.name="Error item", .description="An error has occurred", .speed=500, .duration=5, .maxstack=1, .itemtype=I_INERT, .useeffects=std::vector<std::shared_ptr<effect>>{}});
    additem("i_ironpickaxe", "iron_pickaxe", item{.name="Iron Pickaxe", .description="A pickaxe made from iron", .speed=300, .duration=5, .maxstack=1, .itemtype=I_DIG, .useeffects=std::vector<std::shared_ptr<effect>>{std::make_shared<attackeffect>(10, 1)}});
    additem("i_ironaxe", "iron_axe", item{.name="Iron Axe", .description="An axe made from iron", .speed=400, .duration=5, .maxstack=1, .itemtype=I_DIG, .useeffects=std::vector<std::shared_ptr<effect>>{std::make_shared<attackeffect>(11, 2)}});
    additem("i_apple", "apple", item{.name="Red apple", .description="Delicious red apple", .speed=2000, .duration=0, .maxstack=64, .itemtype=I_CONSUMABLE, .useeffects=std::vector<std::shared_ptr<effect>>{std::make_shared<healeffect>(1)}});
    additem("i_lightbulb", "lightbulb", item{.name="Lightbulb", .description="Emits a decent amount of light", .speed=500, .duration=0, .maxstack=64, .itemtype=I_PLACEABLEOBJECT, .useeffects=std::vector<std::shared_ptr<effect>>{std::make_shared<healeffect>(1)}});
    additem("i_greenwand", "green_wand", item{.name="Green wand", .description="Make weather good", .speed=1000, .duration=0, .maxstack=1, .itemtype=I_USABLE, .useeffects=std::vector<std::shared_ptr<effect>>{std::make_shared<changeweathereffect>(-0.1f)}});
    additem("i_redwand", "red_wand", item{.name="Red wand", .description="Make weather bad", .speed=1000, .duration=0, .maxstack=1, .itemtype=I_USABLE, .useeffects=std::vector<std::shared_ptr<effect>>{std::make_shared<changeweathereffect>(0.1f)}});
    additem("i_timetotem", "totem", item{.name="Time totem", .description="Toggle the movement of time", .speed=1000, .duration=0, .maxstack=1, .itemtype=I_USABLE, .useeffects=std::vector<std::shared_ptr<effect>>{std::make_shared<toggletime>()}});

    //make items from blocks
    for (const tiledata::tileinfo& t : tiledata::gettileinfolist())
    {
        //if (t.ttype == tiledata::T_SOLID || t.ttype == tiledata::T_SOLID_VERT || t.ttype == tiledata::T_DISCARD) //trengs dette?
        //{
            std::string itemid = "i_" + t.name.substr(2, t.name.size()-2);
            int32_t tid = tiledata::gettileid(t.name);
            additem(itemid, t.sidetextures[0], item{.name=t.fullname, .description="Placeable block", .speed=200, .duration=0, .maxstack=64, .itemtype=I_BLOCK, .useeffects=std::vector<std::shared_ptr<effect>>{std::make_shared<changeblockeffect>(true, tid)}});
        //}
    }
}
