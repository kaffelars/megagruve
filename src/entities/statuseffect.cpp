#include "consts.h"
#include "statuseffect.h"

statuseffect::statuseffect(std::string fname, statnumbers cstats, int32_t dur, std::vector<timedeffect> teffects)
{
    fullname=fname;
    changestats=cstats;
    duration=dur;
    for (int a = 0; a < teffects.size(); a++)
    {
        timedeffects.push_back(teffects[a]);
    }
}

statuseffect::~statuseffect()
{
    //dtor
}

void statuseffect::update()
{
    for (timedeffect& t : timedeffects)
    {
        if (t.delay > 0)

        t.delay -= timekeeper::getdeltatime();
        if (t.delay <= 0)
        {
            t.teffect->activate(appliedby.get(), affectedlifeform.get());
            t.delay += t.repeats * t.repeatdelay;
            t.repeats -= 1;
        }
    }

    if (duration < 0) return; //perma buffs

    if (duration > 0)
        duration -= timekeeper::getdeltatime();

    if (duration < 0)
    {
        //destroy
    }

}
