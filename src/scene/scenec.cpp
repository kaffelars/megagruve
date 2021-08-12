#include "consts.h"
#include "scenec.h"

namespace scenec
{
    void addscene(uint32_t id, std::unique_ptr<scene> sceneptr);
    bool quit = false;

    namespace
    {
        uint32_t activescene = 0;
        uint32_t previousscene = 0;
        std::unordered_map<uint32_t, std::unique_ptr<scene>> scenes;
    }
}

void scenec::quitgame()
{
    quit = true;
}

void scenec::initialize()
{
    addscene(S_MAINMENU, std::make_unique<scenemainmenu>());
    addscene(S_SETTINGS, std::make_unique<scenesettings>());
    addscene(S_GAME, std::make_unique<scenegame>());
}

void scenec::addscene(uint32_t sceneid, std::unique_ptr<scene> sceneptr)
{
    scenes.emplace(sceneid, std::move(sceneptr));
    scenes[sceneid] -> initialize();
}

void scenec::returntopreviousscene()
{
    changeactivescene(previousscene);
}

void scenec::changeactivescene(uint32_t changeto)
{
    if (changeto != activescene)
    {
        previousscene = activescene;
        getactivescene().hide();
        activescene = changeto;
        getactivescene().show();
    }
}

scene& scenec::getactivescene()
{
    return *(scenes[activescene]);
}
