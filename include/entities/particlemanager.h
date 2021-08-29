#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H


namespace particlemanager
{
    void initialize();
    void updateparticles();
    void renderparticles();
    void addparticle(wposition p, velocity v, uint8_t ptex, uint8_t psiz, uint32_t dur, uint8_t glo, float gravity, bool destro);
    void cleanup();
    bool anyactiveparticles();
};

#endif // PARTICLEMANAGER_H
