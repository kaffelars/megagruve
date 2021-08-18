#ifndef LIFEFORM_H
#define LIFEFORM_H

#include "entity.h"
#include "statuseffect.h"
#include "statnumbers.h"

class lifeform : public entity
{
    public:
        lifeform();
        virtual ~lifeform();



        virtual wposition getposition();//return physicsobject::getposition(););
        float hp {1};

        void setstats(float hp, float maxhp, float attack, float defense, float movespeed, float usespeed);

        statnumbers basestats; //endres kun av permanente statsendringer
        statnumbers actualstats; //modifies av statuseffects når de settes eller forsvinner
        std::vector<statuseffect> activestatuseffects;

        virtual void heal(uint32_t healamount);
        virtual void takedamage(int32_t attackstrength, int32_t attacktype, entity& source);
        virtual void applybuff(std::string buffname);

        void update();


    protected:

    private:
};

#endif // LIFEFORM_H
