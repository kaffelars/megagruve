#include "consts.h"
#include "uiinventory.h"
//#include "uiingame.h"
#include "vaocontainer.h"
#include "inventorymanager.h"
#include "maincharcontroller.h"
#include "settings.h"

#include "uiicons.h"
#include "itemmanager.h"
#include "inputmanager.h"

namespace uiinventory
{
    struct invslot
    {
        glm::vec2 position;
        inventory* inv;
        int32_t invslot {-1};
        bool canbemovedto{true};
        itemtype itemtypefilter {itemtype::none};
        itemsubtype itemsubtypefilter {itemsubtype::none};
    };

    std::vector<invslot> invslots;

    invslot noslot;

    struct selected
    {
        invslot* selectedinvslot;
        uint8_t selectiontype {0};
    };

    invslot& getinvslotbyposition(glm::ivec2 position);

    selected selectedslot;

    vaocontainer invitemicons;
    vaocontainer invitemborders;

    vaocontainer selection;

    void setselection(invslot& i, int8_t selectiontype = 0);

    struct positiondata
    {
        float iconsize;
        float gridbordersize;
        float spacer;
        float startbar;
    };

    positiondata positionvalues;

    void updatescale();
    void renderstatbox();
    void renderequipmentlabels();
    void renderiteminfobox();

    bool updateinvitems = false;
    bool initialized = false;

    inventory* extrainventory = nullptr;

    inventorytype invtype;
}


void uiinventory::showinventory(inventorytype itype)
{
    setselection(noslot);
    invtype = itype;
}

void uiinventory::setextrainventory(inventory& inv)
{
    extrainventory = &inv;
}

bool uiinventory::inventoryitemsupdated()
{
    return updateinvitems;
}

void uiinventory::initialize()
{

}

void uiinventory::setselection(invslot& i, int8_t selectiontype)
{
    selection.cleanvbos();
    selection.initialize(1, vaocontainer::typo::POINTS, 4);

    selectedslot.selectedinvslot = &i;
    selectedslot.selectiontype = selectiontype;

    if (i.invslot >= 0)
    {
        int32_t texid = texturemanager::geticontexturenumber("clickedborder", texturemanager::ICONS_LARGE);
        if (selectiontype == 2) texid = texturemanager::geticontexturenumber("otherborder", texturemanager::ICONS_LARGE);

        uiicons::additemicon(selection, i.position.x, i.position.y, texid, 1, positionvalues.gridbordersize);
        selection.setvbos();
    }
}

void uiinventory::updateinvslots()
{
    invslots.clear();

    inventory& inv = maincharcontroller::getmcharinventory();

    int row = 0;
    int col = 0;
    int index = 0;

    for (inventory::invitem& i : inv.invitems)
    {
        invslot islot;
        float xpos = col * positionvalues.gridbordersize + positionvalues.startbar;
        float ypos = settings::getscreeny() - row * positionvalues.gridbordersize - positionvalues.gridbordersize * 4.0f;
        if (row > 0) ypos -= positionvalues.gridbordersize / 2.0f;

        islot.position = glm::vec2(xpos, ypos);
        islot.inv = &inv;
        islot.invslot = index;
        invslots.emplace_back(std::move(islot));

        col++;
        index++;
        if (col >= 10)
        {
            col = 0;
            row += 1;
        }
    }

    inventory& mchareq = maincharcontroller::getmainchar().equipment;

    index = 0;
    col = 0;

    for (inventory::invitem& i : mchareq.invitems)
    {
        float xpos = (col + 11.0f) * positionvalues.gridbordersize + positionvalues.startbar;
        float ypos = settings::getscreeny() - 6.5f * positionvalues.gridbordersize + index * positionvalues.gridbordersize - col * positionvalues.gridbordersize * 2.0f;

        invslot islot;
        islot.position = glm::vec2(xpos, ypos);
        islot.inv = &mchareq;
        islot.invslot = index;
        islot.itemtypefilter = itemtype::equipment;
        islot.itemsubtypefilter = itemsubtype::trinket;
        if (index == 0) islot.itemsubtypefilter = itemsubtype::helmet;
        if (index == 1) islot.itemsubtypefilter = itemsubtype::chest;
        if (index == 2) islot.itemsubtypefilter = itemsubtype::boots;
        invslots.emplace_back(std::move(islot));

        index ++;
        if (index == 3) col=1;
    }

    index = 0;
    row = 0;
    col = 0;

    if (invtype == inventorytype::chest)
    {
        for (inventory::invitem& i : extrainventory->invitems)
        {
            invslot islot;
            float xpos = col * positionvalues.gridbordersize + positionvalues.startbar;
            float ypos = settings::getscreeny() - row * positionvalues.gridbordersize - positionvalues.gridbordersize * 10.0f;

            islot.position = glm::vec2(xpos, ypos);
            islot.inv = extrainventory;
            islot.invslot = index;
            invslots.emplace_back(std::move(islot));

            col++;
            index++;
            if (col >= 10)
            {
                col = 0;
                row += 1;
            }
        }
    }
}

void uiinventory::updatescale()
{
    positionvalues.iconsize = (settings::getscreeny() / 1200.0f) * 50.0f * settings::getfsetting(settings::SET_UISCALE);
    positionvalues.spacer = (positionvalues.gridbordersize / 32.0f);

    positionvalues.gridbordersize = (positionvalues.iconsize / 16.0f) * 24.0f;
    positionvalues.startbar = (float(settings::getscreenx()) - (positionvalues.gridbordersize * 9.0f)) / 2.0f;
}

void uiinventory::updategridgfx(bool alsobg)
{
    invitemicons.cleanvbos();
    if (alsobg) invitemborders.cleanvbos();

    invitemicons.initialize(1, vaocontainer::typo::POINTS, 4);
    if (alsobg) invitemborders.initialize(1, vaocontainer::typo::POINTS, 4);

    for (invslot& i : invslots)
    {
        inventory::invitem item = i.inv->getinvitem(i.invslot);

        if (item.quantity > 0)
            uiicons::additemicon(invitemicons, i.position.x, i.position.y, itemmanager::getitem(item.itemid).textureid, item.quantity, positionvalues.iconsize);

        if (alsobg)
        {
            uiicons::additemicon(invitemborders, i.position.x, i.position.y, texturemanager::geticontexturenumber("border", texturemanager::ICONS_LARGE), 1, positionvalues.gridbordersize);
        }

    }

    invitemicons.setvbos();
    if (alsobg) invitemborders.setvbos();
}

uiinventory::invslot& uiinventory::getinvslotbyposition(glm::ivec2 position)
{
    float halfi = positionvalues.iconsize / 2.0f;
    for (invslot& i : invslots)
    {
        if (position.x > i.position.x - halfi && position.x < i.position.x + halfi && position.y > i.position.y - halfi && position.y < i.position.y + halfi)
        {
            return i;
        }
    }

    return noslot;
}

void uiinventory::renderinventory()
{
    if (!initialized)
    {
        updatescale();
        updateinvslots();
        updategridgfx(true);
    }
    if (updateinvitems)
    {
        updateinvslots();
        updategridgfx(false);
    }

    texturemanager::bindiconstexture(texturemanager::ICONS_LARGE, 0);
    invitemborders.render();
    selection.render();
    texturemanager::bindiconstexture(texturemanager::ICONS_MEDIUM, 0);
    invitemicons.render();

    renderstatbox();
    renderequipmentlabels();
    renderiteminfobox();
}

void uiinventory::renderstatbox()
{
    glm::vec2 winsize = glm::vec2(226.0f, 250.0f);
    float ypos = settings::getscreeny() - 4 * positionvalues.gridbordersize - positionvalues.gridbordersize * 4.0f;

    uielement::beginwindow("statbox", glm::ivec2(positionvalues.startbar - winsize.x - positionvalues.iconsize, ypos), winsize);

    uicontroller::changefont(uicontroller::FONT_LARGE);
    uielement::text("Player stats", glm::vec2(10.0f, 10.0f));

    uicontroller::changefont(uicontroller::FONT_NORMAL);

    uielement::text("HP:\n\nAttack:\nDefense:\nMove speed:\nUse speed:\n\nCrabs killed:", glm::vec2(10.0f, 60.0f));

    std::stringstream stattext;
    statnumbers& stats = maincharcontroller::getmainchar().actualstats;
    stattext << maincharcontroller::getcurrenthealth() << "/" << maincharcontroller::getmaxhealth() << "\n\n";

    stattext << stats.statvalues[1] << " + held item\n";
    stattext << stats.statvalues[2] << "\n";
    stattext << stats.statvalues[3] << "\n";
    stattext << stats.statvalues[4] << "\n\n";
    stattext << "0";

    uielement::text(stattext.str(), glm::vec2(120.0f, 60.0f));

    uielement::endwindow();
}

void uiinventory::renderequipmentlabels()
{
    glm::vec2 winsize = glm::vec2(226.0f, 50.0f);

    float xpos = 9.0f * positionvalues.gridbordersize + positionvalues.startbar + positionvalues.iconsize;
    float ypos = settings::getscreeny() - 4 * positionvalues.gridbordersize - positionvalues.gridbordersize * 4.0f;

    uielement::beginwindow("eqlabels", glm::ivec2(xpos, ypos), winsize);

    uicontroller::changefont(uicontroller::FONT_LARGE);
    uielement::text("Equipment", glm::vec2(10.0f, 10.0f));
    uielement::endwindow();
}

void uiinventory::renderiteminfobox()
{

    glm::ivec2 position = inputmanager::getcursorpos();
    invslot& i = getinvslotbyposition(position);

    if (i.invslot >= 0)
    {
        inventory::invitem& hoveritem = i.inv->getinvitem(i.invslot);

        if (hoveritem.quantity > 0)
        {
            uicontroller::changefont(uicontroller::FONT_NORMAL);

            position += glm::ivec2(1,1);

            std::stringstream infotext;
            infotext << itemmanager::getitem(hoveritem.itemid).name << "\n";
            infotext << itemmanager::getitemtypename(hoveritem.itemid) << "\n";
            infotext << itemmanager::getitem(hoveritem.itemid).description << "\n";
            if (itemmanager::getitem(hoveritem.itemid).maxstack > 1) infotext << "Quantity: " << hoveritem.quantity;

            ImVec2 winsize = ImGui::CalcTextSize(infotext.str().c_str(), nullptr);
            winsize.x += 20.0f;
            winsize.y += 5.0f;

            uielement::beginwindow("hoveritem", position, glm::vec2(winsize.x, winsize.y));

            uielement::text(infotext.str(), glm::vec2(10.0f, 0.0f));

            uielement::endwindow();
        }
    }
}

void uiinventory::click(int8_t clicktype)
{
    glm::ivec2 position = inputmanager::getcursorpos();

    invslot& i = getinvslotbyposition(position);

    if (selectedslot.selectedinvslot == &i)
    {
        if (i.invslot >= 0 && invtype == inventorytype::chest)
        {
            if (i.inv == extrainventory) //move from chest to mainchar inv
            {
                inventorymanager::movealltoinv2(*(selectedslot.selectedinvslot->inv), selectedslot.selectedinvslot->invslot, maincharcontroller::getmcharinventory());
            }
            else
            {
                inventorymanager::movealltoinv2(*(selectedslot.selectedinvslot->inv), selectedslot.selectedinvslot->invslot, *extrainventory);
            }
        }
        setselection(noslot);
        updateinvitems = true;
        return; //mover til samme slot
    }

    if (i.invslot >= 0)
    {
        if (selectedslot.selectiontype == 0)
        {
            setselection(i, clicktype+1);
        }
        else
        {
            if (i.canbemovedto)
            {
                if (i.itemtypefilter != itemtype::none)
                {
                    inventory::invitem iitem = selectedslot.selectedinvslot->inv->getinvitem(selectedslot.selectedinvslot->invslot);
                    if (!(itemmanager::getitem(iitem.itemid).itemtype == i.itemtypefilter &&
                        (i.itemsubtypefilter == itemsubtype::none || itemmanager::getitem(iitem.itemid).subtype == i.itemsubtypefilter)))
                        {
                            return;
                        }
                }

                if (selectedslot.selectiontype == 1)
                {
                    if (clicktype == 0)
                    {
                        inventorymanager::swaporcombine(*(selectedslot.selectedinvslot->inv), selectedslot.selectedinvslot->invslot, *(i.inv), i.invslot);
                        setselection(noslot);
                    }
                    else if (clicktype == 1)
                    {
                        if (inventorymanager::moveonlyone(*(selectedslot.selectedinvslot->inv), selectedslot.selectedinvslot->invslot, *(i.inv), i.invslot))
                        {
                            setselection(noslot);
                        }
                    }

                }
                else if (selectedslot.selectiontype == 2)
                {
                    inventorymanager::movehalfstack(*(selectedslot.selectedinvslot->inv), selectedslot.selectedinvslot->invslot, *(i.inv), i.invslot);
                    setselection(noslot);
                }


                updateinvitems = true;

            }
        }
    }
    else
    {
        setselection(noslot);
    }
}
