#ifndef CHUNKTILEMANAGER_H
#define CHUNKTILEMANAGER_H

#include "chunk.h"

namespace chunktilemanager
{
    uint8_t getforwardside(wtilepos wtpos);
    uint8_t getforwardside(chunkpos cpos, ctilepos ctpos);
    void breaktile(wtilepos wtile);
    void explodetiles(wtilepos wtile, int32_t explosionpower);
    bool changectile(chunkpos cpos, ctilepos ctpos, tileid newtileid, uint8_t extrainfo, bool breakage);
    bool changectile(wtilepos wtile, tileid newtileid, uint8_t extrainfo, bool breakage);
    void changetiles();
    void removemapobj(chunk& c, ctilepos ctpos);
    void interactobjaround(chunkpos cpos, ctilepos ctpos, ctilepos effectoffset, mainchar& mchar);

    //std::shared_ptr<map_obj>& getmapobj(wtilepos wtpos);

    void addctiletochange(chunkpos cpos, ctilepos ctpos, tileid newtileid, uint8_t extrainfo, bool breakage);
    void addtiletochange(wtilepos wtile, tileid newtileid, uint8_t extrainfo, bool breakage);
};

#endif // CHUNKTILEMANAGER_H
