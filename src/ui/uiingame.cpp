#include "consts.h"
#include "uiingame.h"

#include "maincharcontroller.h"
#include "vaocontainer.h"
#include "shadercontroller.h"
#include "texturemanager.h"
#include "itemmanager.h"
#include "inventory.h"
#include "settings.h"
#include "statnumbers.h"

#include "inputmanager.h"
#include "uiinventory.h"
#include "uiicons.h"

//kaos, må re-implementeres mer oversiktlig

namespace uiingame
{
    void updatehearts(bool screensizeupdated);
    void updateactionbar(bool screensizeupdated);

    int oldhearts = 0;
    int oldmaxhearts = 0;

    vaocontainer hearts;
    vaocontainer actionbar;
    vaocontainer actionbaritems;

    vaocontainer clickedbox;


    bool showinventory = false;

    int selection = 0;

    int screensizex = settings::getscreenx();
    int screensizey = settings::getscreeny();

    std::vector<uint32_t> numbertotexid;


    struct positiondata
    {
        float iconsize;
        float spacer;
        float startbar;
    };

    positiondata positionvalues;

    void updatevalues();

    struct hitem
    {
        uint32_t itemid;
        uint32_t quantity;
    };

    hitem hoveritem {0,0};

    int32_t invpositiontoswap = -1;

}

void uiingame::resetui()
{
    selection = 0;
    refreshui();
}

void uiingame::refreshui()
{
    updatehearts(true);
    updateactionbar(true);
    updateactionbaritems(true);
}

bool uiingame::showinginventory()
{
    return showinventory;
}

void uiingame::initialize()
{
    for (int a = 0; a < 10; a++)
    {
        uint32_t texid = texturemanager::geticontexturenumber(std::to_string(a), texturemanager::ICONS_MEDIUM);
        numbertotexid.push_back(texid);
    }

    uiicons::initialize();
}

void uiingame::toggleinventory(inventorytype invtype)
{
    showinventory = !showinventory;
    invpositiontoswap = -1;
    if (showinventory)
    {
        uiinventory::showinventory(invtype);
    }
}

void uiingame::updatehearts(bool screensizeupdated)
{
    int mcharhp = maincharcontroller::getcurrenthealth();
    int charmaxhp = maincharcontroller::getmaxhealth();

    if (screensizeupdated || (mcharhp != oldhearts || charmaxhp != oldmaxhearts))
    {
        hearts.initialize(1, vaocontainer::typo::POINTS, 4);
        oldhearts = mcharhp;
        oldmaxhearts = charmaxhp;

        hearts.cleanvbos();

        int index = 0;

        float hiconsize = (positionvalues.iconsize / 90.0f) * 35.0f;
        float hspacer = hiconsize / 2.0f;


        float ypos = (float)screensizey - positionvalues.iconsize * 1.79f;


        for (int a =0; a < charmaxhp; a+=2)
        {
            if (a+2 <= mcharhp)
                hearts.addvalues(0, positionvalues.startbar + (float)a*hspacer, ypos, texturemanager::geticontexturenumber("redheart", texturemanager::ICONS_SMALL),hiconsize);
            else if (a+1 <= mcharhp)
            {
                hearts.addvalues(0, positionvalues.startbar + (float)a*hspacer, ypos, texturemanager::geticontexturenumber("blackheart", texturemanager::ICONS_SMALL),hiconsize);
                hearts.addvalues(0, positionvalues.startbar + (float)a*hspacer, ypos, texturemanager::geticontexturenumber("halfheart", texturemanager::ICONS_SMALL),hiconsize);
            }
            else
            {
                hearts.addvalues(0, positionvalues.startbar + (float)a*hspacer, ypos, texturemanager::geticontexturenumber("blackheart", texturemanager::ICONS_SMALL),hiconsize);
            }
        }

        hearts.setvbos();
    }
}

void uiingame::updateactionbar(bool screensizeupdated)
{
    uint32_t newselection = maincharcontroller::getactionbarselection();

    if (screensizeupdated || actionbar.isempty() || selection != newselection)
    {
        selection = newselection;

        actionbar.cleanvbos();

        actionbar.initialize(1, vaocontainer::typo::POINTS, 4);


        float ypos = (float)screensizey - positionvalues.iconsize;

        for (int a = 0; a < 10; a++)
        {
            if (a == selection)
                actionbar.addvalues(0, positionvalues.startbar + (float)a*(positionvalues.spacer + positionvalues.iconsize), ypos, texturemanager::geticontexturenumber("selectedborder", texturemanager::ICONS_LARGE),positionvalues.iconsize);
            else
                actionbar.addvalues(0, positionvalues.startbar + (float)a*(positionvalues.spacer + positionvalues.iconsize), ypos, texturemanager::geticontexturenumber("border", texturemanager::ICONS_LARGE),positionvalues.iconsize);
        }

        actionbar.setvbos();
    }
}

void uiingame::updatevalues()
{
    positionvalues.iconsize = (screensizey / 1200.0f) * 90.0f * settings::getfsetting(settings::SET_UISCALE);
    positionvalues.spacer = (positionvalues.iconsize / 32.0f);
    positionvalues.startbar = ((float)screensizex - (positionvalues.iconsize * 9.0f) - (positionvalues.spacer * 9.0f)) / 2.0f;
}


void uiingame::updateactionbaritems(bool updatebar)
{
    if (updatebar || actionbaritems.isempty())
    {
        actionbaritems.cleanvbos();

        actionbaritems.initialize(1, vaocontainer::typo::POINTS, 4);

        std::vector<uint32_t> itemtextures; //temp for testing, fyll via maincharctrl
        std::vector<uint32_t> quantity;

        inventory& mcharinv = maincharcontroller::getmcharinventory();

        for (int a = 0; a < 10; a++)
        {
            if (mcharinv.getinvitem(a).quantity > 0)
            {
                uint32_t itemid = mcharinv.getinvitem(a).itemid;
                itemtextures.push_back(itemmanager::getitem(itemid).textureid);
                quantity.push_back(mcharinv.getinvitem(a).quantity);
            }
            else
            {
                itemtextures.push_back(0);
                quantity.push_back(0);
            }
        }


        float aiconsize = positionvalues.iconsize * 0.6667f;

        float ypos = (float)screensizey - positionvalues.iconsize;

        for (int a = 0; a < 10; a++)
        {
            if (itemtextures[a] != 0)
                uiicons::additemicon(actionbaritems, positionvalues.startbar + (float)a*(positionvalues.iconsize + positionvalues.spacer), ypos, itemtextures[a], quantity[a], aiconsize);
        }

        actionbaritems.setvbos();
    }
}

void uiingame::rendergameui()
{
    bool screensizeupdated = false;
    if (screensizex != settings::getscreenx() || screensizey != settings::getscreeny())
    {
        screensizex = settings::getscreenx();
        screensizey = settings::getscreeny();
        screensizeupdated = true;

        updatevalues();
    }

    updatehearts(screensizeupdated);
    updateactionbar(screensizeupdated);
    updateactionbaritems(screensizeupdated);
    //updateinventory(screensizeupdated, true);

    shadercontroller::activateshader(shadercontroller::SH_ICONS);
    glUniform2f(shadercontroller::getuniformid("screensize"), screensizex, screensizey);

    texturemanager::bindiconstexture(texturemanager::ICONS_SMALL, 0);

    hearts.render();

    texturemanager::bindiconstexture(texturemanager::ICONS_LARGE, 0);

    actionbar.render();

    texturemanager::bindiconstexture(texturemanager::ICONS_MEDIUM, 0);

    actionbaritems.render();

    if (showinventory)
    {
        if (uiinventory::inventoryitemsupdated())
        {
            updateactionbaritems(true);
        }

        uiinventory::renderinventory();
    }

}
