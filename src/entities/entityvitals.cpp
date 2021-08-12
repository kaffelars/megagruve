#include "consts.h"
#include "entityvitals.h"

entityvitals::entityvitals(uint32_t fmaxhp, uint32_t farmor) : maxhp{fmaxhp}, armor{farmor}
{
    hp = maxhp - 3;
}

entityvitals::entityvitals() = default;


entityvitals::~entityvitals()
{
    //dtor
}

void entityvitals::takedamage(uint32_t damage)
{
    uint32_t damagenumber = (damage - armor);
    if (damagenumber > 0)
        hp -= damagenumber;

    if (hp < 0)
    {
        alive =false;
    }
}

void entityvitals::heal(uint32_t healing)
{
    hp += healing;
    if (hp > maxhp)
        hp = maxhp;
}

bool entityvitals::isalive()
{
    return alive;
}

void entityvitals::update()
{
    auto sef = statuseffects.begin();

    while(sef != statuseffects.end()) {
        (*sef).duration--;
        if ((*sef).duration <0)
        {
            removestatuseffect(sef);
        }
        else ++sef;
    }
}

void entityvitals::removestatuseffect(std::vector<s_effect>::iterator index)
{
    statuseffects.erase(index);
}

void entityvitals::removestatuseffect(uint32_t index)
{
    removestatuseffect(statuseffects.begin() + index);
}
