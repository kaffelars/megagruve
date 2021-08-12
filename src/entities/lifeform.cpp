#include "consts.h"
#include "lifeform.h"

#include "statuseffectmanager.h"

lifeform::lifeform()
{
    //ctor
}

lifeform::~lifeform()
{
    //dtor
}

wposition lifeform::getposition()
{
    //fjern denne func, la physicsobj ordne biffen
}

void lifeform::heal(uint32_t healamount)
{
    hp += healamount;
    if (hp > actualstats.maxhp) hp = actualstats.maxhp;
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

    if (hp > actualstats.maxhp) hp = actualstats.maxhp;
}
