#ifndef LIFEFORM_H
#define LIFEFORM_H

#include "entity.h"
#include "statuseffect.h"
#include "statnumbers.h"
#include "physicsobject.h"

class lifeform : public entity, public physicsobject
{
    public:
        lifeform(wposition p, velocity v, point b, bbtype btyp, float gfactor);
        virtual ~lifeform();



        wposition getposition();//return physicsobject::getposition(););

        float hp {1};

        void setstats(float hp, float maxhp, float attack, float defense, float movespeed, float usespeed);

        statnumbers basestats; //endres kun av permanente statsendringer
        statnumbers actualstats; //modifies av statuseffects n�r de settes eller forsvinner
        std::vector<statuseffect> activestatuseffects;

        virtual void heal(int32_t healamount);
        virtual void takedamage(int32_t attackstrength, int32_t attacktype, entity& source);
        virtual void applybuff(std::string buffname);

        void update();


    protected:

    private:
};

#endif // LIFEFORM_H
