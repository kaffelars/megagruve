#include "consts.h"
#include "entity.h"

#include "tiledata.h"
#include "chunkcontroller.h"
#include "modelmanager.h"
#include "chunktilemanager.h"

void entity::heal(int32_t healamount) {}
void entity::takedamage(int32_t attackstrength, int32_t attacktype, entity* source) {};
void entity::applybuff(std::string buffname) {};
wposition entity::getposition() {return wposition{0.0f,0.0f,0.0f};};
//void entity::setposition(wposition wpos);
int32_t entity::getid() {return 0;};
bool entity::interact() {return false;}; //for right click
bool entity::destroy() {return false;};
model& entity::getmodel() {return modelmanager::getemptymodel();}
void entity::setfacingdirection(tilesideid tsid)
{
    facingdirection = tsid;
}

direction entity::getviewdir()
{
    glm::ivec3 of = sideoffsets[static_cast<int>(facingdirection)];
    return direction{of.x, of.y, of.z};
};

int32_t entity::getfacingdirectionid()
{
    return static_cast<int32_t>(facingdirection);
}


blockentity::blockentity(wtilepos tilepos) {
    wtpos = tilepos;
    resethealth();
}

wposition blockentity::getposition() {
    return wposition (wtpos);
}

void blockentity::setposition(wtilepos tilepos) {
    wtpos = tilepos;
    resethealth();
}

void blockentity::resethealth()
{
    if (tiledata::isinitialized())
        health = tiledata::gettileinfo(getid()).hardness;
    else
        health = 0;
}

bool blockentity::destroy()
{
    chunktilemanager::breaktile(wtpos);
    return true;
}

int32_t blockentity::getcurrenthealth()
{
    return health;
}

void blockentity::heal(int32_t healamount)
{
    health += healamount;
}

void blockentity::takedamage (int32_t attackstrength, int32_t attacktype, entity* source)
{
    //sjekk
    if (!tiledata::isempty(getid()) && health < 255) //255 = uknuselig
    {
        health -= attackstrength;
        if (health <= 0) destroy();
    }
}

int32_t blockentity::getid()
{
    return chunkcontroller::gettileid(wtpos);
}


/*class itementity :: public entity
{
	//for invitems? nje
};*/
