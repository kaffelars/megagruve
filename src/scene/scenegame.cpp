#include "consts.h"
#include "scenegame.h"

scenegame::scenegame()
{
    //ctor
}

scenegame::~scenegame()
{
    //dtor
}

void scenegame::initialize()
{

}

void scenegame::show()
{
    camera::updateperspective();

    if (showingescbox)
        inputmanager::showmouse();
    else
        inputmanager::hidemouse();

}

void scenegame::hide()
{
    inputmanager::showmouse();
}

void scenegame::render()
{
    renderer::rendergame();

    uielement::beginwindow("infobox", glm::vec2(1.0f), glm::vec2(190.0f, 100.0f));

    wposition mcpos = maincharcontroller::getmaincharposition();
    std::stringstream infotext;
    infotext << "x:" << std::roundf(mcpos.x) << " y:" << std::roundf(mcpos.y) << " z:" << std::roundf(mcpos.z) << "\n";

    wtilepos selectedtile = maincharcontroller::gettilehover();

    infotext << "tile coords: " << selectedtile.x << " " << selectedtile.y << " " << selectedtile.z << "\n";

    tileid tid = chunkcontroller::gettileid(selectedtile);
    infotext << "tilename: " << tiledata::gettilename(tid) << "\n";

    infotext << "loaded: " << chunkcontroller::loadedchunksnum() << "\nrendered: " << chunkcontroller::getchunksrendered();

    uielement::text(infotext.str(), glm::vec2(10.0f, 0.0f));

    uielement::endwindow();

}

void scenegame::shutdownworld()
{
    //blabla save chunks unload shit etc
}

void scenegame::toggleescbox()
{
    showingescbox = !showingescbox;

    if (showingescbox)
        inputmanager::showmouse();
    else
        inputmanager::hidemouse();
}

void scenegame::update()
{
    if (inputmanager::waskeyclicked(inputmanager::KEY_ESCAPE))
    {
        toggleescbox();
    }

    if (showingescbox)
    {
        escbox::selection sel = escbox::showescbox();
        if (sel == escbox::selection::QUIT)
        {
            shutdownworld();
            scenec::quitgame();
        }
        if (sel == escbox::selection::MENU)
        {
            shutdownworld();
            scenec::changeactivescene(scenec::S_MAINMENU);
        }
        if (sel == escbox::selection::BACK)
        {
            toggleescbox();
        }
        if (sel == escbox::selection::SETTINGS)
        {
            scenec::changeactivescene(scenec::S_SETTINGS);
        }
    }
    else
    {
        environment::updatetime();
        //input etc
        maincharcontroller::inputactions();
        maincharcontroller::movement();

        maincharcontroller::updatecamera();
    }

    chunkcontroller::updatechunks();
}

void scenegame::destroy()
{

}
