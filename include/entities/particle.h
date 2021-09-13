#ifndef PARTICLE_H
#define PARTICLE_H

#include "physicsobject.h"
#include "effect.h"
#include "entity.h"

class particle : public physicsobject
{
    public:
        particle(wposition p, velocity v, uint8_t ptex, uint8_t psiz, uint32_t dur, uint8_t glo, float gravity, bool destro);
        virtual ~particle();

        uint8_t textureid;
        uint8_t particlesize;
        uint32_t duration;
        uint8_t glow;
        bool destroyedwhenlanding;

        std::vector<std::shared_ptr<effect>> landingeffects;
        entity* createdby {nullptr};

    protected:

    private:
};

#endif // PARTICLE_H
