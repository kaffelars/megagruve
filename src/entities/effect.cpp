#include "consts.h"
#include "effect.h"
#include "chunkcontroller.h"
#include "tiledata.h"
#include "environment.h"
#include "particlemanager.h"
#include "maincharcontroller.h"

healeffect::healeffect(int32_t healstr) : healstrength{healstr}
{

}

bool healeffect::activate(entity* user, entity* target)
{
    target->heal(healstrength);

    return true;
}

togglelight::togglelight(float lightstr) : lightstrength{lightstr}
{

}

bool togglelight::activate(entity* user, entity* target)
{
    maincharcontroller::togglelight(lightstrength);
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


shootparticle::shootparticle(uint32_t particlenum, uint8_t particletex, int32_t particlespread) : num{particlenum}, texid{particletex}, spread{particlespread}
{

}

bool shootparticle::activate(entity* user, entity* target)
{
    for (int a = 0; a < num; a++)
    {
        float randx = utils::randint(-spread, spread);
        float randy = utils::randint(-spread, spread);
        float randz = utils::randint(-spread, spread);
        randx /= 30.0f;
        randy /= 30.0f;
        randz /= 30.0f;
        wposition pos = target->getposition();
        particlemanager::addparticle(pos, velocity(randx, randy, randz), texid, 15, 5000, 0, 0.5f, true);
    }
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

toggleflying::toggleflying()
{

}

bool toggleflying::activate(entity* user, entity* target)
{
    maincharcontroller::toggleflying();
    return true;
}


explodeblocks::explodeblocks(uint32_t explosionpower) : power{explosionpower}
{

}

bool explodeblocks::activate(entity* user, entity* target)
{
    wtilepos wt = target->getposition();
    chunkcontroller::explodetiles(wt, power);
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

    chunkcontroller::addtiletochange(wt, tid, false);
    /*tileid tid = (uint8_t)target->getid();
    chunkcontroller::changewtile(wt, tid);*/

    return true;
}
