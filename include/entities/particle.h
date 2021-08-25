#ifndef PARTICLE_H
#define PARTICLE_H

#include "physicsobject.h"

class particle : public physicsobject
{
    public:
        particle(wposition p, velocity v, uint8_t ptex, uint8_t psiz, uint32_t dur, uint8_t glo);
        virtual ~particle();

        uint8_t textureid;
        uint8_t particlesize;
        uint32_t duration;
        uint8_t glow;

    protected:

    private:
};

#endif // PARTICLE_H
