#include "consts.h"
#include "effect.h"
#include "chunkcontroller.h"
#include "tiledata.h"
#include "environment.h"


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




changeweathereffect::changeweathereffect(float weatherchange) : change{weatherchange}
{

}

bool changeweathereffect::activate(entity* user, entity* target)
{
    environment::changecloudcover(change);
    return true;
}


toggletime::toggletime()
{

}

bool toggletime::activate(entity* user, entity* target)
{
    environment::toggletimemoving();
    return true;
}



changeblockeffect::changeblockeffect(bool onlyemptyblocks, tileid block) : emptyonly{onlyemptyblocks}, tid{block}
{

}

bool changeblockeffect::activate(entity* user, entity* target)
{
    //target er blockentity, sjekk om luft?
    /*if (emptyonly) //uncomment dis
    {
        if (!tiledata::isempty(target->getid())) return false;
    }*/
    //std::cout << target->getposition().x << " " << target->getposition().y << " " << target->getposition().z << "\n";
    wtilepos wt = target->getposition();//chunkcontroller::wpostowtilepos(target->getposition());
    //std::cout << wt.x << " " << wt.y << " " << wt.z << "\n";
    target->heal(99999); //kan dette by på problemer?

    chunkcontroller::addtiletochange(wt, tid);
    /*tileid tid = (uint8_t)target->getid();
    chunkcontroller::changewtile(wt, tid);*/

    return true;
}
