#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "effect.h"

namespace particlemanager
{
    void initialize();
    void updateparticles();
    void renderparticles();
    void addparticle(wposition p, velocity v, uint8_t ptex, uint8_t psiz, uint32_t dur, uint8_t glo, float gravity, bool destro);
    void addcomplexparticle(wposition p, velocity v, uint8_t ptex, uint8_t psiz, uint32_t dur, uint8_t glo, float gravity, bool destro, entity* caster, std::vector<std::shared_ptr<effect>> landingeffects);
    void cleanup();
    bool anyactiveparticles();
};

#endif // PARTICLEMANAGER_H
