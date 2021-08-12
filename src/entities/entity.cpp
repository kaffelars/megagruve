#include "consts.h"
#include "entity.h"

#include "tiledata.h"
#include "chunkcontroller.h"

void entity::heal(uint32_t healamount) {}
void entity::takedamage(int32_t attackstrength, int32_t attacktype, entity* source) {};
void entity::applybuff(std::string buffname) {};
wposition entity::getposition() {};
int32_t entity::getid() {};


blockentity::blockentity(wtilepos tilepos) {
    resethealth();
    wtpos = tilepos;
}

wposition blockentity::getposition() {
    return wposition (wtpos);
}

void blockentity::resethealth()
{
    health = tiledata::gettileinfo(getid()).hardness;
}

void blockentity::destroytile()
{
    chunkcontroller::breaktile(wtpos);
}

void blockentity::takedamage (int32_t attackstrength, int32_t attacktype, entity* source)
{
    //sjekk
    if (!tiledata::isempty(getid()))
    {
        health -= attackstrength;
        if (health < 0) destroytile();
    }
}

int32_t blockentity::getid()
{
    return chunkcontroller::gettileid(wtpos);;
}


/*class itementity :: public entity
{
	//for invitems? nje
};*/
