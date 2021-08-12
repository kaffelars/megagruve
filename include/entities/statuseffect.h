#ifndef STATUSEFFECT_H
#define STATUSEFFECT_H

#include "effect.h"
#include "statnumbers.h"
#include "entity.h"
#include "timekeeper.h"

class statuseffect
{
    public:
        struct timedeffect
        {
            timedeffect(int32_t idelay, int32_t irepeats, int32_t irepeatdelay, std::shared_ptr<effect> iteffect) : delay{idelay}, repeats{irepeats}, repeatdelay{irepeatdelay}, teffect{iteffect}
            { }
            int32_t delay; //ms delay før start, brukes også som counter for repeatdelay
            int32_t repeats; //number
            int32_t repeatdelay; //ms mellom hver repeat
            std::shared_ptr<effect> teffect;
        };

        statuseffect(std::string fname, statnumbers cstats, int32_t dur, std::vector<timedeffect> teffects);
        virtual ~statuseffect();




        std::string fullname;
        statnumbers changestats; //endrer f.eks. attack, walking speed, osv.
        int32_t duration; //varighet i ms, hvis ikke satt settes basert på lengden av timeeffects’, hvis negativ = infinite
        std::vector<timedeffect> timedeffects;
        uint32_t textureid {0};
        std::shared_ptr<entity> affectedlifeform;
        std::shared_ptr<entity> appliedby;
        void update(); //kjøres hver frame
};

#endif // STATUSEFFECT_H
