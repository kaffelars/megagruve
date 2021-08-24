#include "consts.h"
#include "uiingame.h"

#include "maincharcontroller.h"
#include "vaocontainer.h"
#include "shadercontroller.h"
#include "texturemanager.h"
#include "itemmanager.h"
#include "inventory.h"
#include "settings.h"

#include "inputmanager.h"

namespace uiingame
{
    void updatehearts(bool screensizeupdated);
    void updateactionbar(bool screensizeupdated);

    void additemicon(vaocontainer& vaoc, float xpos, float ypos, uint32_t textureid, uint32_t quantity, float iconsize);

    int oldhearts = 0;
    int oldmaxhearts = 0;

    vaocontainer hearts;
    vaocontainer actionbar;
    vaocontainer actionbaritems;

    vaocontainer clickedbox;

    vaocontainer selecteditem;

    vaocontainer inventorybg;
    vaocontainer inventoryitems;

    bool showinventory = false;

    int selection = 0;

    int screensizex = settings::getscreenx();
    int screensizey = settings::getscreeny();

    std::vector<uint32_t> numbertotexid;

    void updateclickedbox();

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

void uiingame::initialize()
{
    for (int a = 0; a < 10; a++)
    {
        uint32_t texid = texturemanager::geticontexturenumber(std::to_string(a), texturemanager::ICONS_MEDIUM);
        numbertotexid.push_back(texid);
    }
}

void uiingame::toggleinventory()
{
    showinventory = !showinventory;
    invpositiontoswap = -1;
}

void uiingame::additemicon(vaocontainer& vaoc, float xpos, float ypos, uint32_t textureid, uint32_t quantity, float iconsize)
{
    vaoc.addvalues(0, xpos, ypos, textureid, iconsize);
    if (quantity > 1)
    {
        int8_t digits[3] {-1, -1, -1};
        digits[2] = quantity % 10;
        if (quantity > 9)
        {
            digits[1] = quantity / 10 %10;
        }
        if (quantity > 99) {
            digits[0] = quantity / 100 %10;
        }

        float numbericonsize = iconsize / 3.0f;

        for (int a = 0; a < 3; a++)
        {
            if (digits[a] != -1)
                vaoc.addvalues(0, (xpos+numbericonsize*(a-1)), ypos+numbericonsize*1.1f, numbertotexid[digits[a]], numbericonsize);
        }

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

void uiingame::updateinventory(bool update, bool alsobg)
{
    if (update)
    {
        inventory& inv = maincharcontroller::getmcharinventory();
        int rows = inv.getinvsize() / 10;

        float deltay = screensizey - positionvalues.iconsize * 5.5f;
        float dy;

        if (alsobg)
        {
            inventorybg.cleanvbos();
            inventorybg.initialize(1, vaocontainer::typo::POINTS, 4);

            for (int y = 1; y < rows; y++)
            {
                for (int x = 0; x < 10; x++)
                {
                    dy = deltay;

                    inventorybg.addvalues(0, positionvalues.startbar + x * (positionvalues.iconsize + positionvalues.spacer), dy + y * positionvalues.iconsize,
                                          texturemanager::geticontexturenumber("border", texturemanager::ICONS_LARGE),positionvalues.iconsize);
                }
            }

            inventorybg.setvbos();
        }

        inventoryitems.cleanvbos();
        inventoryitems.initialize(1, vaocontainer::typo::POINTS, 4);

        uint32_t itemtexture;
        uint32_t itemquantity;
        float iiconsize = (positionvalues.iconsize / 24.0f) * 16.0f;

        uint32_t index = 10;
        uint32_t texid;

        for (int y = 1; y < rows; y++)
        {
            for (int x = 0; x < 10; x++)
            {
                dy = deltay;

                inventory::invitem i = inv.getinvitem(index);

                texid = itemmanager::getitem(i.itemid).textureid;

                if (texid)
                    additemicon(inventoryitems, positionvalues.startbar + x * (positionvalues.iconsize + positionvalues.spacer), dy + y * positionvalues.iconsize, texid , i.quantity, iiconsize);

                index++;
            }
        }

        inventoryitems.setvbos();
    }
}

void uiingame::hover()
{
    hoveritem.itemid = 0;
    hoveritem.quantity = 0;

    if (showinventory)
    {
        glm::ivec2 position = inputmanager::getcursorpos();
        float deltay = screensizey - positionvalues.iconsize * 5.5f;
        if (position.x > (positionvalues.startbar - positionvalues.iconsize / 2) && position.x < screensizex - (positionvalues.startbar - positionvalues.iconsize / 2) && position.y > deltay)
        {

            int32_t index = getinvitemidbyposition(position);

            if (index >= 0)
            {
                inventory& i = maincharcontroller::getmcharinventory();
                inventory::invitem item = i.getinvitem(index);
                hoveritem.itemid = item.itemid;
                hoveritem.quantity = item.quantity;
            }
        }
    }
}

int32_t uiingame::getinvitemidbyposition(glm::ivec2 position)
{
    inventory& i = maincharcontroller::getmcharinventory();

    uint32_t index = 0;
    int rows = i.getinvsize() / 10;
    float deltay = screensizey - positionvalues.iconsize * 5.5f;
    uint32_t dy = deltay;

    float halficonsize= positionvalues.iconsize / 2.0f;

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            if (y == 0) dy = (float)screensizey - positionvalues.iconsize;
            else dy = deltay;

            uint32_t px = positionvalues.startbar + x * (positionvalues.iconsize + positionvalues.spacer);
            uint32_t py = dy + y * positionvalues.iconsize;
            if (position.x > px - halficonsize && position.x < px + halficonsize && position.y > py - halficonsize && position.y < py + halficonsize)
            {
                return index;
            }

            index++;
        }
    }

    return -1;
}

void uiingame::click()
{
    glm::ivec2 position = inputmanager::getcursorpos();
    int32_t index = getinvitemidbyposition(position);

    if (index >= 0)
    {
        if (invpositiontoswap != -1)
        {
            inventory& i = maincharcontroller::getmcharinventory();
            i.swaporcombineitems(invpositiontoswap, index);
            invpositiontoswap = -1;
            updateactionbaritems(true);
            updateinventory(true, false);
        }
        else
        {
            invpositiontoswap = index;
            updateclickedbox();
        }
    }
    else
    {
        invpositiontoswap = -1;
    }
}

void uiingame::updateclickedbox()
{
    clickedbox.cleanvbos();
    clickedbox.initialize(1, vaocontainer::typo::POINTS, 4);

    float deltay = screensizey - positionvalues.iconsize * 5.5f;
    float dy = deltay;

    if (invpositiontoswap >= 0)
    {
        float x = invpositiontoswap % 10;
        float y = invpositiontoswap / 10;

        if (y == 0) dy = (float)screensizey - positionvalues.iconsize;
        else dy = deltay;

        float px = positionvalues.startbar + x * (positionvalues.iconsize + positionvalues.spacer);
        float py = dy + y * positionvalues.iconsize;

        clickedbox.addvalues(0, px, py, texturemanager::geticontexturenumber("clickedborder", texturemanager::ICONS_LARGE),positionvalues.iconsize);
    }

    clickedbox.setvbos();
}

void uiingame::renderiteminfobox()
{
    if (hoveritem.itemid)
    {
        uicontroller::changefont(uicontroller::FONT_NORMAL);
        float winwidth = ImGui::CalcTextSize(itemmanager::getitem(hoveritem.itemid).description.c_str(), nullptr).x + 20.0f;
        float nwidth = ImGui::CalcTextSize(itemmanager::getitem(hoveritem.itemid).name.c_str(), nullptr).x + 20.0f;
        if (nwidth > winwidth) winwidth = nwidth;
        if (winwidth < 100.0f) winwidth = 100.0f;

        glm::ivec2 position = inputmanager::getcursorpos() + glm::ivec2(1,1);
        uielement::beginwindow("hoveritem", position, glm::vec2(winwidth, 60));

        std::stringstream infotext;
        infotext << itemmanager::getitem(hoveritem.itemid).name << "\n";
        infotext << itemmanager::getitem(hoveritem.itemid).description << "\n";
        infotext << "Quantity: " << hoveritem.quantity;
        uielement::text(infotext.str(), glm::vec2(10.0f, 0.0f));
        uielement::endwindow();
    }
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
                additemicon(actionbaritems, positionvalues.startbar + (float)a*(positionvalues.iconsize + positionvalues.spacer), ypos, itemtextures[a], quantity[a], aiconsize);
        }

        actionbaritems.setvbos();
    }
}

void uiingame::rendergameui()
{
    hover();

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
    updateinventory(screensizeupdated, true);

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
        texturemanager::bindiconstexture(texturemanager::ICONS_LARGE, 0);
        inventorybg.render();
        texturemanager::bindiconstexture(texturemanager::ICONS_MEDIUM, 0);
        inventoryitems.render();
        if (invpositiontoswap >= 0)
        {
            texturemanager::bindiconstexture(texturemanager::ICONS_LARGE, 0);
            clickedbox.render();
        }
        renderiteminfobox();
    }

}
