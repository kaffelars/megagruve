#include "consts.h"
#include "timedfunctions.h"

#include "timekeeper.h"

namespace timedfunctions
{
    struct timedfunction
    {
        float timer;
        std::function<void()> timedfunc;
    };

    std::vector<timedfunction> tfuncs;
}

void timedfunctions::addtimedfunction(float timer, std::function<void()> timedfunc)
{
    timedfunction t;
    t.timer = timer;
    t.timedfunc = timedfunc;

    tfuncs.emplace_back(std::move(t));
}

void timedfunctions::update() //litt kronglete pga. at timed funcs can adde ny func
{
    std::vector<timedfunction> tfuncs2;

    for (timedfunction& t: tfuncs)
    {
        tfuncs2.emplace_back(std::move(t));
    }

    tfuncs.clear();

    for (timedfunction& t: tfuncs2)
    {
        t.timer -= timekeeper::getcappeddeltatime();

        if (t.timer < 0.0f)
        {
            t.timedfunc();
        }
        else
        {
            tfuncs.emplace_back(std::move(t));
        }
    }
}
