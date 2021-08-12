#include "consts.h"
#include "uiingame.h"

#include "maincharcontroller.h"
#include "vaocontainer.h"
#include "shadercontroller.h"
#include "texturemanager.h"
#include "itemmanager.h"
#include "inventory.h"
#include "settings.h"

namespace uiingame
{
    void updatehearts(bool screensizeupdated);
    void updateactionbar(bool screensizeupdated);
    void updateactionbaritems(bool screensizeupdated);

    int oldhearts = 0;
    int oldmaxhearts = 0;

    vaocontainer hearts;
    vaocontainer actionbar;
    vaocontainer actionbaritems;

    int selection = 0;

    int screensizex = settings::getscreenx();
    int screensizey = settings::getscreeny();

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

        float iconsize = (screensizey / 1200.0f) * 35.0f * settings::getfsetting(settings::SET_UISCALE);
        float spacer = iconsize / 2.0f;

        float aiconsize = (screensizey / 1200.0f) * 90.0f * settings::getfsetting(settings::SET_UISCALE);
        float aspacer = (aiconsize / 32.0f);
        float startbar = ((float)screensizex - (aiconsize * 9.0f) - (aspacer * 9.0f)) / 2.0f;

        float ypos = (float)screensizey - aiconsize * 2.0f;


        for (int a =0; a < charmaxhp; a+=2)
        {
            if (a+2 <= mcharhp)
                hearts.addvalues(0, startbar + (float)a*spacer, ypos, texturemanager::geticontexturenumber("redheart", texturemanager::ICONS_SMALL),iconsize);
            else if (a+1 <= mcharhp)
            {
                hearts.addvalues(0, startbar + (float)a*spacer, ypos, texturemanager::geticontexturenumber("blackheart", texturemanager::ICONS_SMALL),iconsize);
                hearts.addvalues(0, startbar + (float)a*spacer, ypos, texturemanager::geticontexturenumber("halfheart", texturemanager::ICONS_SMALL),iconsize);
            }
            else
            {
                hearts.addvalues(0, startbar + (float)a*spacer, ypos, texturemanager::geticontexturenumber("blackheart", texturemanager::ICONS_SMALL),iconsize);
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

        float iconsize = (screensizey / 1200.0f) * 90.0f * settings::getfsetting(settings::SET_UISCALE);
        float spacer = (iconsize / 32.0f);
        float startbar = ((float)screensizex - (iconsize * 9.0f) - (spacer * 9.0f)) / 2.0f;

        float ypos = (float)screensizey - iconsize;

        for (int a = 0; a < 10; a++)
        {
            if (a == selection)
                actionbar.addvalues(0, startbar + (float)a*(spacer + iconsize), ypos, texturemanager::geticontexturenumber("selectedborder", texturemanager::ICONS_LARGE),iconsize);
            else
                actionbar.addvalues(0, startbar + (float)a*(spacer + iconsize), ypos, texturemanager::geticontexturenumber("border", texturemanager::ICONS_LARGE),iconsize);
        }

        actionbar.setvbos();
    }
}

void uiingame::updateactionbaritems(bool screensizeupdated)
{
    if (screensizeupdated || actionbaritems.isempty())
    {
        actionbaritems.cleanvbos();

        actionbaritems.initialize(1, vaocontainer::typo::POINTS, 4);

        std::vector<uint32_t> itemtextures; //temp for testing, fyll via maincharctrl

        inventory& mcharinv = maincharcontroller::getmcharinventory();

        for (int a = 0; a < 10; a++)
        {
            if (mcharinv.getinvitem(a).quantity > 0)
            {
                uint32_t itemid = mcharinv.getinvitem(a).itemid;
                itemtextures.push_back(itemmanager::getitem(itemid).textureid);
            }
            else
            {
                itemtextures.push_back(0);
            }
        }


        float aiconsize = (screensizey / 1200.0f) * 90.0f * settings::getfsetting(settings::SET_UISCALE);
        float aspacer = (aiconsize / 32.0f);
        //float astartbar = ((float)screensizex - (iconsize * 9.0f) - (spacer * 9.0f)) / 2.0f;

        float iconsize = aiconsize * 0.6667f;

        float startbar = ((float)screensizex - (aiconsize * 9.0f) - (aspacer * 9.0f)) / 2.0f;

        float ypos = (float)screensizey - aiconsize;

        for (int a = 0; a < 10; a++)
        {
            if (itemtextures[a] != 0)
                actionbaritems.addvalues(0, startbar + (float)a*(aiconsize + aspacer), ypos, itemtextures[a] ,iconsize);
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
    }

    updatehearts(screensizeupdated);
    updateactionbar(screensizeupdated);
    updateactionbaritems(screensizeupdated);

    shadercontroller::activateshader(shadercontroller::SH_ICONS);
    glUniform2f(shadercontroller::getuniformid("screensize"), screensizex, screensizey);

    texturemanager::bindiconstexture(texturemanager::ICONS_SMALL, 0);

    hearts.render();

    texturemanager::bindiconstexture(texturemanager::ICONS_LARGE, 0);

    actionbar.render();

    texturemanager::bindiconstexture(texturemanager::ICONS_MEDIUM, 0);

    actionbaritems.render();
}
