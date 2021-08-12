#include "consts.h"
#include "statuseffectmanager.h"

#include "texturemanager.h"

namespace statuseffectmanager
{
    std::vector<statuseffect> defaultstatuseffects;
    std::unordered_map<std::string, int32_t> seffectnametoid;
    void adddefaultstatuseffect(std::string name, std::string texture, statuseffect s);
}

uint32_t statuseffectmanager::getstatuseffectid(std::string name)
{
    if (seffectnametoid.find(name) == seffectnametoid.end()) return 0;
    return seffectnametoid.at(name);
}

statuseffect statuseffectmanager::getstatuseffect(std::string name)
{
	return defaultstatuseffects[getstatuseffectid(name)];
}

void statuseffectmanager::initialize()
{
    adddefaultstatuseffect("b_weakheal", "apple",
    statuseffect("Heal over time",statnumbers {},0, std::vector<statuseffect::timedeffect>{
    statuseffect::timedeffect(1000, 4, 4, std::make_shared<healeffect>(2))
    }));

    /*adddefaultstatuseffect("b_weakshieldbuff", "shield",
    statuseffect {.fullname="Shield buff", .changestats=statnumbers {.maxhp=0,.attack=0,.defense=2,.movespeed=0.0f, .usespeed = 0.0f},
    duration=10000, std::vector<statuseffect::timedeffect>{}
    }}*/

}

void statuseffectmanager::adddefaultstatuseffect(std::string name, std::string texture, statuseffect s)
{
    defaultstatuseffects.push_back(createstatuseffect(name, texture, s));

    uint32_t id = defaultstatuseffects.size()-1;
    seffectnametoid.insert(std::make_pair(name, id));
}


statuseffect statuseffectmanager::createstatuseffect(std::string name, std::string texture, statuseffect s)
{
	s.textureid = texturemanager::geticontexturenumber(texture, texturemanager::ICONS_SMALL);
	if (s.duration == 0)
    {
        for (statuseffect::timedeffect& t : s.timedeffects)
        {
            int tempduration = t.delay + (t.repeats-1) * t.repeatdelay;
            if (tempduration > s.duration) s.duration = tempduration;
        }
    }
}

