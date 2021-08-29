#include "consts.h"
#include "scenegame.h"

#include "chunkcoords.h"
#include "uiingame.h"
#include "particlemanager.h"

scenegame::scenegame()
{

}

scenegame::~scenegame()
{
    //dtor
}

void scenegame::initialize()
{

}

void scenegame::setkeys()
{
    inputmanager::setkeyfunction(inputmanager::KEY_ESCAPE, [&](){toggleescbox();}, inputmanager::KE_CLICKED);

    inputmanager::setkeyfunction(inputmanager::KEY_ZOOMIN, [&](){maincharcontroller::changeselectiondelta(-1);}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_ZOOMOUT, [&](){maincharcontroller::changeselectiondelta(1);}, inputmanager::KE_CLICKED);

    inputmanager::setkeyfunction(inputmanager::KEY_1, [&](){maincharcontroller::changeselection(0);}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_2, [&](){maincharcontroller::changeselection(1);}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_3, [&](){maincharcontroller::changeselection(2);}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_4, [&](){maincharcontroller::changeselection(3);}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_5, [&](){maincharcontroller::changeselection(4);}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_6, [&](){maincharcontroller::changeselection(5);}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_7, [&](){maincharcontroller::changeselection(6);}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_8, [&](){maincharcontroller::changeselection(7);}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_9, [&](){maincharcontroller::changeselection(8);}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_0, [&](){maincharcontroller::changeselection(9);}, inputmanager::KE_CLICKED);

    inputmanager::setkeyfunction(inputmanager::KEY_UP, [&](){maincharcontroller::movechar(hdirection(0, 1));}, inputmanager::KE_HELD);
    inputmanager::setkeyfunction(inputmanager::KEY_DOWN, [&](){maincharcontroller::movechar(hdirection(0, -1));}, inputmanager::KE_HELD);
    inputmanager::setkeyfunction(inputmanager::KEY_LEFT, [&](){maincharcontroller::movechar(hdirection(1, 0));}, inputmanager::KE_HELD);
    inputmanager::setkeyfunction(inputmanager::KEY_RIGHT, [&](){maincharcontroller::movechar(hdirection(-1, 0));}, inputmanager::KE_HELD);

    inputmanager::setkeyfunction(inputmanager::KEY_SELECT, [&](){maincharcontroller::useselecteditem();}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_SELECT, [&](){maincharcontroller::useselecteditem();}, inputmanager::KE_HELD);

    inputmanager::setkeyfunction(inputmanager::KEY_INV, [&](){toggleinventory();}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_TOGGLEFLYING, [&](){maincharcontroller::toggleflying();}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_JUMP, [&](){maincharcontroller::mcharjump();}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_JUMP, [&](){maincharcontroller::mcharjump();}, inputmanager::KE_HELD);
}

void scenegame::show()
{
    camera::updateperspective();

    setkeys();

    if (showingescbox)
    {
        inputmanager::pausekeyfunctions();
        inputmanager::showmouse();
    }
    else
    {
        inputmanager::hidemouse();
        inputmanager::resumekeyfunctions();
    }
}

void scenegame::hide()
{
    inputmanager::showmouse();
    inputmanager::clearallkeyfunctions();
}

void scenegame::render()
{
    renderer::rendergame();

    uielement::beginwindow("infobox", glm::vec2(1.0f), glm::vec2(190.0f, 180.0f));

    wposition mcpos = maincharcontroller::getmaincharposition();
    std::stringstream infotext;
    infotext << "x:" << std::roundf(mcpos.x) << " y:" << std::roundf(mcpos.y) << " z:" << std::roundf(mcpos.z) << "\n";

    wtilepos selectedtile = maincharcontroller::gettilehover();

    infotext << "tile coords: " << selectedtile.x << " " << selectedtile.y << " " << selectedtile.z << "\n";

    wtilepos wtpos = maincharcontroller::gettilehoverentityposition();

    infotext << "ctilepos: " << wtpos.x << " " << wtpos.y << " " << wtpos.z << "\n";

    chunkpos cpos = chunkcoords::wpostocpos(wposition{wtpos} + wposition{0.5f});
    ctilepos ctpos = chunkcoords::wpostoctilepos(wposition{wtpos} + wposition{0.5f});

    infotext << "chunk: " << cpos.x << " " << cpos.y << "\n";
    infotext << "ctpos: " << ctpos.x << " " << ctpos.y << " " << ctpos.z << "\n";

    tileid tid = chunkcontroller::gettileid(selectedtile);
    infotext << "tilename: " << tiledata::gettilename(tid) << "\n";

    if (chunkcontroller::chunkexists(cpos))
    {
        chunk& c = chunkcontroller::getchunk(cpos);
        if (c.gettag()==chunk::C_READY)
        {
            chunk::biomedata biome = c.getbiome(ctpos);
            infotext << "temp: " << int(biome.temperature) << " humid: " << int(biome.humidity) << "\n";
        }
    }
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
    {
        if (showinginventory)
        {
            toggleinventory();
        }
        inputmanager::pausekeyfunctions();
        inputmanager::showmouse();
    }
    else
    {
        inputmanager::hidemouse();
        inputmanager::resumekeyfunctions();
    }

}

void scenegame::toggleinventory()
{
    showinginventory = !showinginventory;

    if (showinginventory)
    {
        inputmanager::setkeyfunction(inputmanager::KEY_SELECT, [&](){uiingame::click();}, inputmanager::KE_CLICKED);
        inputmanager::setkeyfunction(inputmanager::KEY_SELECT, [&](){}, inputmanager::KE_HELD);
        uiingame::toggleinventory();
        inputmanager::showmouse();
        //inputmanager::setkeyfunction(inputmanager::KEY_SELECT, [&](){maincharcontroller::useselecteditem();}, inputmanager::KE_CLICKED);
        //inputmanager::setkeyfunction(inputmanager::KEY_SELECT, [&](){maincharcontroller::useselecteditem();}, inputmanager::KE_HELD);
    }
    else
    {
        setkeys();
        uiingame::toggleinventory();
        inputmanager::hidemouse();
        //inputmanager::resumekeyfunctions();
        //inputmanager::setkeyfunction(inputmanager::KEY_SELECT, [&](){maincharcontroller::useselecteditem();}, inputmanager::KE_CLICKED);
        //inputmanager::setkeyfunction(inputmanager::KEY_SELECT, [&](){maincharcontroller::useselecteditem();}, inputmanager::KE_HELD);
    }
}

void scenegame::update()
{
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
    else if (showinginventory)
    {

    }
    else
    {
        //std::cout << "\n1";
        environment::updatetime();
        //std::cout << "2";
        maincharcontroller::update(); //her kræsjer det - eller kanskje ikke??
        //std::cout << "3";
        particlemanager::updateparticles();
        //std::cout << "4";
    }

    chunkcontroller::updatechunks();

    //std::cout << "5\n";
}

void scenegame::destroy()
{

}
