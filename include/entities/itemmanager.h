#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "maincharcontroller.h"
#include "texturemanager.h"
#include "effect.h"
#include "tiledata.h"

namespace itemmanager
{
    /*enum itemtypes
    {
        I_BLOCK, I_DIG, I_USABLE, I_CONSUMABLE, I_INERT, I_EQUIPMENT, I_PLACEABLEOBJECT, I_FLAG
    };

    enum subtypes
    {
        IS_HELMET, IS_CHEST, IS_BOOTS, IS_TRINKET, IS_OTHER
    };*/

    struct item
    {
        std::string name;
        std::string description;

        uint32_t speed; //millisekunder mellom hver use
        uint32_t duration;

        uint32_t maxstack {32};

        itemtype itemtype;
        itemsubtype subtype;

        std::vector<std::shared_ptr<effect>> useeffects; //hmm

        maincharcontroller::smode selectionmode; //selection mode når item er selected

        uint32_t textureid;
    };

    void additem(std::string itemid, std::string texturename, item itemtoadd);

    item& getitem(uint32_t itemnumid);
    uint32_t getflagidbytextureid(uint32_t texid);
    uint32_t getitemid(std::string itemid);
    void initialize();

    std::string getitemtypename(uint32_t itemnumid);
};

#endif // ITEMMANAGER_H
