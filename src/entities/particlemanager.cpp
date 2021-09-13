#include "consts.h"
#include "particlemanager.h"

#include "particle.h"
#include "particlevao.h"
#include "utils.h"
#include "timekeeper.h"
#include "chunkcontroller.h"
#include "chunk.h"
#include "physicsmanager.h"
#include "entity.h"

namespace particlemanager
{
    std::vector<particle> particles;
    particlevao particlesvao;
}

void particlemanager::addparticle(wposition p, velocity v, uint8_t ptex, uint8_t psiz, uint32_t dur, uint8_t glo, float gravity, bool destro)
{
    particles.emplace_back(particle(p, v, ptex, psiz, dur, glo, gravity, destro));
}

void particlemanager::addcomplexparticle(wposition p, velocity v, uint8_t ptex, uint8_t psiz, uint32_t dur, uint8_t glo, float gravity, bool destro, entity* caster, std::vector<std::shared_ptr<effect>> landingeffects)
{
    particles.emplace_back(particle(p, v, ptex, psiz, dur, glo, gravity, destro));
    int pid = particles.size() - 1;

    particles[pid].createdby = caster;

    for (std::shared_ptr<effect> le : landingeffects)
    {
        particles[pid].landingeffects.push_back(le);
    }
}

void particlemanager::initialize()
{

}

void particlemanager::updateparticles()
{
    std::vector<particle> ps; //ikke helt bra
    ps.reserve(particles.size());
    //updates particles
    for (particle& p: particles)
    {
        p.duration -= timekeeper::getcappeddeltatime();
        if (p.duration > 0)
        {
            physicsmanager::pointphysics(p);
            //p.dophysics();
        }

        if (p.duration <= 0 || (p.onfloor && p.destroyedwhenlanding))
        {
            if (!p.landingeffects.empty())
            {
                //landing effects
                for (std::shared_ptr<effect>& le : p.landingeffects)
                {
                    wposition wpos = p.getposition();
                    blockentity b(wtilepos(wpos.x, wpos.y, wpos.z));
                    le->activate(p.createdby, &b);
                }
            }
        }
        else
        {
            ps.push_back(std::move(p));
        }
    }

    particles.clear();

    for (particle& p : ps)
    {
        particles.push_back(std::move(p));
    }

    /*particles.clear();

    for (particle& p : ps)
    {
        particles.push_back(p);
    }*/

    //std::remove_if(particles.begin(), particles.end(), [](const particle &p) { return (p.duration <= 0); }); //tregt

    //renser vekk døde particles //tregt
    /*auto vit = particles.begin();
    while (vit != particles.end())
    {
        if ((*vit).duration <= 0 || ((*vit).onfloor && (*vit).destroyedwhenlanding))
        {
            if (!(*vit).landingeffects.empty())
            {
                //landing effects
                for (std::shared_ptr<effect>& le : (*vit).landingeffects)
                {
                    wposition wpos = (*vit).getposition();
                    blockentity b(wtilepos(wpos.x, wpos.y, wpos.z));
                    le->activate((*vit).createdby, &b);
                }
            }
            vit = particles.erase(vit);
        }
        else
        {
            ++vit;
        }
    }*/
}

bool particlemanager::anyactiveparticles()
{
    return !particles.empty();
}

void particlemanager::renderparticles()
{
    particlesvao.cleanvbos();

    for (particle& p: particles)
    {
        wposition pp = p.getposition();
        particlesvao.addvalues(0, pp.x, pp.y, pp.z, 0.0f);

        rgbcolor255 light = rgbcolor255(255, 255, 255);
        chunk::tlight tl = chunkcontroller::getlight(pp);
        uint8_t sunlight = tl.sunlight * 17;
        uint8_t ambocc = 0;

        float packedlight = utils::packu2f(light.x, light.y, light.z);
        float packeddiv = utils::packu2f(sunlight, p.textureid, p.glow);
        float packedost = utils::packu2f(p.particlesize, 0, 0);
        particlesvao.addvalues(1, packedost, packeddiv, packedlight, 0.0f);
    }

    particlesvao.setvbos();


    particlesvao.render();
}

void particlemanager::cleanup()
{
    particlesvao.cleanvbos();
}
