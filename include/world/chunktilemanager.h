#ifndef CHUNKTILEMANAGER_H
#define CHUNKTILEMANAGER_H

#include "chunk.h"

namespace chunktilemanager
{
    struct breakageinfo
    {
        bool breakage {false};
        velocity particlevel {direction(0.0f,0.0f,0.0f)};
        uint8_t particlenum {3};
    };

    uint8_t getforwardside(wtilepos wtpos);
    uint8_t getforwardside(chunkpos cpos, ctilepos ctpos);
    void breaktile(wtilepos wtile);
    void breaktilewithinfo(wtilepos wtile, breakageinfo b);
    void explodetiles(wtilepos wtile, int32_t explosionpower);
    void addtilelight(ctilepos ctp, chunkpos cpo, uint8_t lightstrength);
    bool changectile(chunkpos cpos, ctilepos ctpos, tileid newtileid, uint8_t extrainfo, breakageinfo breakage, uint8_t forwardside = 0, bool updateneighbour = true);
    bool changectile(wtilepos wtile, tileid newtileid, uint8_t extrainfo, breakageinfo breakage, uint8_t forwardside = 0);
    void changetiles();
    void removemapobj(chunk& c, ctilepos ctpos);
    void interactobjaround(chunkpos cpos, ctilepos ctpos, ctilepos effectoffset, mainchar& mchar);

    //std::shared_ptr<map_obj>& getmapobj(wtilepos wtpos);

    void addctiletochange(chunkpos cpos, ctilepos ctpos, tileid newtileid, uint8_t extrainfo, breakageinfo breakage);
    void addtiletochange(wtilepos wtile, tileid newtileid, uint8_t extrainfo, breakageinfo breakage);
    void cleartilestochange();
    bool checkoutsidetiles(chunk& c);
};

#endif // CHUNKTILEMANAGER_H
