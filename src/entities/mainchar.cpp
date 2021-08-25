#include "consts.h"
#include "mainchar.h"

mainchar::mainchar()
{
    //ctor

}

mainchar::~mainchar()
{
    //dtor
}

void mainchar::fillinv()
{
    mcharinv.additem("i_ironpickaxe", 1);
    mcharinv.additem("i_timetotem", 1);
    mcharinv.additem("i_apple", 5);
    mcharinv.additem("i_greenwand", 1);
    mcharinv.additem("i_planks", 64);
    mcharinv.additem("i_flag", 32);
    mcharinv.additem("i_redwand", 1);
    mcharinv.additem("i_glowstone", 65);
    mcharinv.additem("i_stone", 99);
    mcharinv.additem("i_bookcase", 77);

    mcharinv.additem("i_cactus", 56);
    mcharinv.additem("i_apple", 13);
    mcharinv.additem("i_sand", 64);
    mcharinv.additem("i_flower2", 64);
    mcharinv.additem("i_planks", 64);
    mcharinv.additem("i_rock", 64);
    mcharinv.additem("i_ironaxe", 1);
    mcharinv.additem("i_snow", 1);
    mcharinv.additem("i_ironpickaxe", 1);
    mcharinv.additem("i_ironpickaxe", 1);

    mcharinv.additem("i_ironpickaxe", 1);
    mcharinv.additem("i_ironpickaxe", 1);


}

wposition mainchar::geteyeposition()
{
    return pobject.getposition() + cameraoffset;
}

wposition mainchar::getposition()
{
    return pobject.getposition();
}

void mainchar::updatecamera()
{
    camera::updateviewmatrix(geteyeposition(), rot);
}

direction mainchar::getviewdir()
{
    //fubar
    float kex = ((float)rot.x*pi_value/180)/3;
    float key = ((float)rot.y*pi_value/180)/3;

    return glm::normalize(direction(sin(kex)*cos(key), sin(key), cos(kex)*cos(key)));
}

hdirection mainchar::gethviewdir()
{
    //fubar
    float kex = ((float)rot.x*pi_value/180)/3;
    float key = ((float)rot.y*pi_value/180)/3;

    return glm::normalize(hdirection(sin(kex)*cos(key), cos(kex)*cos(key)));
}

void mainchar::addvelocity(direction vel)
{
    pobject.addvelocity(vel);
}

void mainchar::movehoriz(hdirection movement)
{
    hdirection dir = gethviewdir();

    direction hmovement = glm::vec3(0.0f);

    hmovement.x = dir.x * movement.y;
    hmovement.z = dir.y * movement.y;

    hmovement.x += -dir.y * movement.x;
    hmovement.z += dir.x * movement.x;

    pobject.addposition(hmovement*timekeeper::gettimefactor());
}

void mainchar::moveflying(hdirection movement)
{
    direction dir = getviewdir();
    hdirection hdir = gethviewdir();

    direction dmovement = glm::vec3(0.0f);

    dmovement.x = dir.x * movement.y;
    dmovement.y = dir.y * movement.y;
    dmovement.z = dir.z * movement.y;

    dmovement.x += -hdir.y * movement.x;
    //dmovement.y += dir.y * movement.x;
    dmovement.z += hdir.x * movement.x;

    pobject.addposition(dmovement*timekeeper::gettimefactor());
}

void mainchar::rotateview(rotation r)
{
    rot.x += r.x;
    rot.y += r.y;

    if (rot.x > 1080) rot.x -= 1080;
    if (rot.x < 0) rot.x += 1080;
    utils::clamp(rot.y, -270, 270);
}
