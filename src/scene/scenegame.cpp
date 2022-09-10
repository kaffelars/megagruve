#include "consts.h"
#include "scenegame.h"

#include "chunkcoords.h"
#include "uiingame.h"
#include "particlemanager.h"
#include "uiinventory.h"
#include "scenegamehelperfunctions.h"
#include "timedfunctions.h"
#include "newgenerator.h"

scenegame::scenegame()
{

}

scenegame::~scenegame()
{
    //dtor
}

void scenegame::initialize()
{
    scenegamehelperfunctions::setscenepointer(this);
}

void scenegame::setkeys()
{
    inputmanager::setkeyfunction(inputmanager::KEY_ESCAPE, [&](){pressedesc();}, inputmanager::KE_CLICKED);

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

    inputmanager::setkeyfunction(inputmanager::KEY_INTERACT, [&](){maincharcontroller::interact();}, inputmanager::KE_CLICKED);

    //inputmanager::setkeyfunction(inputmanager::KEY_INTERACT, [&](){newgenerator::printgenvalues(chunkcontroller::getchunk(chunkcoords::wpostocpos(maincharcontroller::getmaincharposition())));}, inputmanager::KE_CLICKED);

    inputmanager::setkeyfunction(inputmanager::KEY_INV, [&](){toggleinventory();}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_TOGGLEFLYING, [&](){maincharcontroller::toggleflying();maincharcontroller::togglenoclip();}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_TOGGLEINFOBOX, [&](){showinfobox = !showinfobox;}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_RUNNING, [&](){maincharcontroller::currentlyrunning();}, inputmanager::KE_HELD);
    inputmanager::setkeyfunction(inputmanager::KEY_SNEAKING, [&](){maincharcontroller::currentlysneaking();}, inputmanager::KE_HELD);
    inputmanager::setkeyfunction(inputmanager::KEY_JUMP, [&](){maincharcontroller::mcharjump();}, inputmanager::KE_CLICKED);
    inputmanager::setkeyfunction(inputmanager::KEY_JUMP, [&](){maincharcontroller::mcharjump();}, inputmanager::KE_HELD);
}

void scenegame::show()
{
    camera::updateperspective();

    renderer::updaterenderfilter();

    setkeys();

    uiingame::refreshui();

    if (startnewworld)
    {
        showingescbox = false;
        startnewworld = false;
    }

    if (showingescbox)
    {
        inputmanager::pausekeyfunctionsexcept(std::vector<inputmanager::keys_enum> {inputmanager::KEY_ESCAPE});
        maincharcontroller::setmaincharcameramoveable(false);
        inputmanager::showmouse();
    }
    else
    {
        inputmanager::hidemouse();
        maincharcontroller::setmaincharcameramoveable(true);
        inputmanager::resumeallkeyfunctions();
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

    if (showinfobox)
    {
        uielement::beginwindow("infobox", glm::vec2(1.0f), glm::vec2(190.0f, 240.0f));

        wposition mcpos = maincharcontroller::getmaincharposition();
        std::stringstream infotext;
        infotext << "x:" << std::roundf(mcpos.x) << " y:" << std::roundf(mcpos.y) << " z:" << std::roundf(mcpos.z) << "\n";

        wtilepos selectedtile = maincharcontroller::gettilehover();

        infotext << "selected tile: " << selectedtile.x << " " << selectedtile.y << " " << selectedtile.z << "\n";

        wtilepos wtpos = maincharcontroller::gettilehoverentityposition();

        infotext << "tile hover: " << wtpos.x << " " << wtpos.y << " " << wtpos.z << "\n";

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
                infotext << "light: " << int(c.getsunlight(ctpos)) << "\n";
            }
        }
        infotext << "loaded: " << chunkcontroller::loadedchunksnum() << "\nrendered: " << chunkcontroller::getchunksrendered() << "\n";

        infotext << "time: " << std::round(environment::getcurrenttime() * 100) / 100.0f << "\n";

        infotext << "seed: " << randfunc::getseed();

        uielement::text(infotext.str(), glm::vec2(10.0f, 0.0f));

        uielement::endwindow();
    }
}

void scenegame::shutdownworld()
{
    //blabla save chunks unload shit etc
}

void scenegame::pressedesc()
{
    if (showinginventory)
    {
        toggleinventory();
    }
    else
    {
        showingescbox = !showingescbox;

        if (showingescbox)
        {
            /*if (showinginventory)
            {
                toggleinventory();
            }*/
            //inputmanager::pausekeyfunctions();
            inputmanager::pausekeyfunctionsexcept(std::vector<inputmanager::keys_enum> {inputmanager::KEY_ESCAPE});
            maincharcontroller::setmaincharcameramoveable(false);
            inputmanager::showmouse();
        }
        else
        {
            inputmanager::hidemouse();
            maincharcontroller::setmaincharcameramoveable(true);
            inputmanager::resumeallkeyfunctions();
        }
    }

}

void scenegame::toggleinventory(inventorytype invtype)
{
    scenegamehelperfunctions::toggleinventory(invtype);
}

void scenegame::hiddenupdate()
{
    if (lastwasfocus)
    {
        wasmousehidden = inputmanager::ismousehidden();
        inputmanager::showmouse();
        lastwasfocus = false;
    }
}

void scenegame::update()
{
    if (!lastwasfocus)
    {
        wasmousehidden ? inputmanager::hidemouse() : inputmanager::showmouse();
        lastwasfocus = true;
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
            startnewworld = true;
            shutdownworld();
            scenec::changeactivescene(scenec::S_MAINMENU);
        }
        if (sel == escbox::selection::BACK)
        {
            pressedesc();
        }
        if (sel == escbox::selection::SETTINGS)
        {
            scenec::changeactivescene(scenec::S_SETTINGS);
        }
    }
    else
    {
        timedfunctions::update();

        environment::updatetime();

        maincharcontroller::update();
    }

    chunkcontroller::updatechunks();

    if (!showingescbox)
        particlemanager::updateparticles();
}

void scenegame::destroy()
{

}

void scenegame::changewindowsize()
{

}
