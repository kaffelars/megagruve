#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include "scene.h"
#include "scenemainmenu.h"
#include "scenesettings.h"
#include "scenegame.h"
#include "scenegameinitializer.h"

namespace scenec
{
    enum sceneids
    {
        S_MAINMENU, S_SETTINGS, S_GAME, S_GAMEINITIALIZER, S_BLANK
    };

    void quitgame();
    void initialize();
    void changeactivescene(uint32_t changeto);
    scene& getactivescene();

    void returntopreviousscene();

    extern bool quit;
};

#endif // SCENECONTROLLER_H
