#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

//trengs alt dette? nje
#include "scene.h"
#include "scenec.h"

#include "vaocontainer.h"
#include "shader.h"

#include "settings.h"
#include "uicontroller.h"
#include "inputmanager.h"
#include "windowmanager.h"

#include "skybox.h"
#include "scenequad.h"

#include "shadercontroller.h"
#include "framebuffercontroller.h"

#include "timekeeper.h"


namespace gamecontroller
{
    void gameloop();

    void timekeeping();

    void render();



    void close();


};

#endif // GAMECONTROLLER_H
