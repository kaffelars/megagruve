#include "consts.h"
#include "gamecontroller.h"
#include "windowmanager.h"
#include "uicontroller.h"
#include "settings.h"
#include "scenec.h"
#include "skybox.h"
#include "scenequad.h"
#include "shadercontroller.h"
#include "framebuffercontroller.h"
#include "inputmanager.h"
#include "tiledata.h"
#include "texturemanager.h"
#include "voxelmodels.h"
#include "maincharcontroller.h"
#include "itemmanager.h"
#include "uiingame.h"
#include "biomecontroller.h"
#include "map_obj_models.h"
#include "environment.h"
#include "particlemanager.h"

int main( int argc, char* args[] )
{
    std::cout << "starting megagruve ...\n";

    settings::loadsettings(); //loader inn settings, må være først

    windowmanager::initialize();
    uicontroller::setupimgui();

    texturemanager::initialize();
    tiledata::initialize();
    itemmanager::initialize();
    uiingame::initialize();

    voxelmodels::initialize();

    biomecontroller::initialize();

    particlemanager::initialize();

    std::cout << "initializing skybox & scenequad... ";
    skybox::initialize();
    std::cout << "skybox done... ";
    scenequad::initialize();
    std::cout << "scenequad done!\n";

    //stuff
    shadercontroller::initialize();
    framebuffercontroller::initialize();
    inputmanager::initialize();
    //

    environment::initialize();

    scenec::initialize();

    map_obj_models::initialize();

    maincharcontroller::initialize();

    gamecontroller::gameloop();//selve gamet

    return 0;
}


