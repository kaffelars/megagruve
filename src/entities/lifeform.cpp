#include "consts.h"
#include "lifeform.h"

#include "statuseffectmanager.h"

lifeform::lifeform(wposition p, velocity v, point b, bbtype btyp, float gfactor) : physicsobject(p, v, b, btyp, gfactor)
{
    //ctor
}

lifeform::~lifeform()
{
    //dtor
}

void lifeform::setstats(float shp, float maxhp, float attack, float defense, float movespeed, float usespeed)
{
    basestats.setstat(statnumbers::STAT_MAXHP, maxhp);
    hp = shp;
    if (hp == 0.0f) hp = maxhp;
    basestats.setstat(statnumbers::STAT_ATTACK, attack);
    basestats.setstat(statnumbers::STAT_DEFENSE, defense);
    basestats.setstat(statnumbers::STAT_MOVESPEED, movespeed);
    basestats.setstat(statnumbers::STAT_USESPEED, usespeed);
}

wposition lifeform::getposition()
{
    return physicsobject::getposition();
}

void lifeform::heal(int32_t healamount)
{
    hp += healamount;
    if (hp > actualstats.getstat(statnumbers::STAT_MAXHP)) hp = actualstats.getstat(statnumbers::STAT_MAXHP);
}

void lifeform::takedamage(int32_t attackstrength, int32_t attacktype, entity& source)
{
    hp -= attackstrength;
    if (hp < 0) hp = 0;
}


void lifeform::applybuff(std::string buffname)
{
    activestatuseffects.push_back(statuseffectmanager::getstatuseffect(buffname));
}

void lifeform::update()
{
	//oppdaterer alt
	actualstats = basestats;
	for (statuseffect& s : activestatuseffects)
	{
		actualstats = basestats + s.changestats;
		s.update();
    }

    //tatt falldamage?
    if (physicsobject::falldamage)
    {
        blankentity bentity;
        takedamage(physicsobject::falldamage, 3, bentity);
        physicsobject::falldamage = 0;
    }

    if (hp > actualstats.getstat(statnumbers::STAT_MAXHP)) hp = actualstats.getstat(statnumbers::STAT_MAXHP);
}
