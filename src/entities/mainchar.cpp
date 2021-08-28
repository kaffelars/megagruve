#include "consts.h"
#include "mainchar.h"

mainchar::mainchar() : lifeform(wposition{50.5f, 78.0f, 0.5f},
            velocity{0.0f, 0.0f, 0.0f},
            point{0.4f, 1.8f, 0.4f},
            physicsobject::BB_BOX,
            1.0f)
{
    flying = true;
    toggleflying();

}

mainchar::~mainchar()
{
    //dtor
}

void mainchar::toggleflying()
{
    flying = !flying;
    if (flying)
    {
        physicsobject::gravityfactor = 0.0f;
    }
    else
    {
        physicsobject::gravityfactor = 1.0f;
    }
}

void mainchar::fillinv()
{
    mcharinv.additem("i_diamondpickaxe", 1);
    mcharinv.additem("i_timetotem", 1);
    mcharinv.additem("i_apple", 5);
    mcharinv.additem("i_greenwand", 1);
    mcharinv.additem("i_planks", 64);
    mcharinv.additem("i_wings", 1);
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
    mcharinv.additem("i_ironsword", 1);
    mcharinv.additem("i_fireball", 1);
    mcharinv.additem("i_diamond", 33);
    mcharinv.additem("i_planks", 64);
    mcharinv.additem("i_planks", 64);
    mcharinv.additem("i_planks", 64);
    mcharinv.additem("i_flag", 64);

    mcharinv.additem("i_apple_golden", 13);


}

wposition mainchar::geteyeposition()
{
    return getposition() + cameraoffset;
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


void mainchar::movehoriz(hdirection movement)
{
    hdirection dir = gethviewdir();

    direction hmovement = glm::vec3(0.0f);

    hmovement.x = dir.x * movement.y;
    hmovement.z = dir.y * movement.y;

    hmovement.x += -dir.y * movement.x;
    hmovement.z += dir.x * movement.x;

    hmovement.y = vel.y;

    setvelocity(hmovement);
}

void mainchar::moveflying(hdirection movement)
{
    direction dir = getviewdir();
    hdirection hdir = gethviewdir();

    direction dmovement = glm::vec3(0.0f);

    dmovement.x = dir.x * movement.y;
    dmovement.y = dir.y * movement.y + vel.y;
    dmovement.z = dir.z * movement.y;

    dmovement.x += -hdir.y * movement.x;
    //dmovement.y += dir.y * movement.x;
    dmovement.z += hdir.x * movement.x;

    setvelocity(dmovement);
}

void mainchar::rotateview(rotation r)
{
    rot.x += r.x;
    rot.y += r.y;

    if (rot.x > 1080) rot.x -= 1080;
    if (rot.x < 0) rot.x += 1080;
    utils::clamp(rot.y, -270, 270);
}
