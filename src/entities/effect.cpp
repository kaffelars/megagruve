#include "consts.h"
#include "effect.h"
#include "chunkcontroller.h"
#include "tiledata.h"


healeffect::healeffect(int32_t healstr) : healstrength{healstr}
{

}

bool healeffect::activate(entity* user, entity* target)
{
    target->heal(healstrength);

    return true;
}



applybuff::applybuff(std::string bname) : buffname{bname}
{

}

bool applybuff::activate(entity* user, entity* target)
{
    //target.status(buffid);
    target->applybuff(buffname);

    return true;
}


attackeffect::attackeffect(int32_t attackstr, int32_t atype) : attackstrength{attackstr}, attacktype{atype}
{

}

bool attackeffect::activate(entity* user, entity* target)
{
	target->takedamage(attackstrength, attacktype, user);

	return true;
}


changeblockeffect::changeblockeffect(bool onlyemptyblocks, tileid block) : emptyonly{onlyemptyblocks}, tid{block}
{

}

bool changeblockeffect::activate(entity* user, entity* target)
{
    //target er blockentity, sjekk om luft?
    if (emptyonly)
    {
        if (!tiledata::isempty(target->getid())) return false;
    }

    wtilepos wt = chunkcontroller::wpostowtilepos(target->getposition());

    chunkcontroller::addtiletochange(wt, target->getid());

    return true;
}
