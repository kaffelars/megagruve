#include "consts.h"
#include "maincharcontroller.h"

#include "mainchar.h"
#include "inputmanager.h"
#include "utils.h"
#include "renderer.h"
#include "chunkcontroller.h"
#include "itemmanager.h"
#include "effect.h"
#include "uiingame.h"
#include "entity.h"
#include "chunkmesh.h"
#include "settings.h"
#include "physicsmanager.h"
#include "blocktracer.h"

#include "chunkcoords.h"

namespace maincharcontroller
{
    mainchar mchar;
    wtilepos tilehover = wtilepos(0,0,0);
    wtilepos oldtilehover = wtilepos(0,0,0);

    tilesideid tilesidehover = tilesideid::xm;
    tilesideid oldtilesidehover = tilesideid::xm;

    vaocontainer selection;
    smode selectionmode = SEL_BLOCK;

    hdirection hmovement = glm::vec2(0.0f);

    blockentity tilehoverentity (wtilepos(0, 0, 0));

    bool cameramoveable = true;

    chunkmesh destructorblock[4];

    float mcharlight = 0.0f;
}

void maincharcontroller::setmaincharcameramoveable(bool moveable)
{
    cameramoveable = moveable;
}

mainchar& maincharcontroller::getmainchar() //trengs denne nå? ja, brukes i uiingame stats
{
    return mchar;
}

void maincharcontroller::interact()
{
    chunkcontroller::interactobj(tilehover, mchar);
}

void maincharcontroller::togglelight(float lightstr)
{
    if (mcharlight == 0.0f)
        mcharlight = lightstr;
    else
        mcharlight = 0.0f;
}

float maincharcontroller::getmcharlight()
{
    return mcharlight;
}

void maincharcontroller::movechar(hdirection dir)
{
    hmovement += dir;
    hmovement = glm::clamp(hmovement, -1.0f, 1.0f);
}

inventory& maincharcontroller::getmcharinventory()
{
    return mchar.mcharinv;
}

int32_t maincharcontroller::getcurrenthealth()
{
    return mchar.lifeform::hp;
}
int32_t maincharcontroller::getmaxhealth()
{
    return mchar.lifeform::actualstats.getstat(statnumbers::STAT_MAXHP);
}

int32_t maincharcontroller::getactionbarselection()
{
    return mchar.actionbarselection;
}

maincharcontroller::smode maincharcontroller::getselectionmode()
{
    return selectionmode;
}

void maincharcontroller::setselectionmode(smode selmode)
{
    selectionmode = selmode;
}

void maincharcontroller::renderselection()
{
    wtilepos selpos = maincharcontroller::gettilehover();

    if (selpos.y != -1)
    {
        wposition vpos = wposition(selpos) - mchar.geteyeposition();
        glUniform3f(shadercontroller::getuniformid("vpos"), vpos.x, vpos.y, vpos.z);

        if (settings::getisetting(settings::SET_MBOX) && getselectionmode() == SEL_BLOCK)
        {
            glUniform3f(shadercontroller::getuniformid("rgb"), 0.8f, 0.7f, 0.7f);
            selection.render();
        }
        else if (settings::getisetting(settings::SET_BBOX) && getselectionmode() == SEL_AIR)
        {
            glUniform3f(shadercontroller::getuniformid("rgb"), 0.8f, 0.8f, 1.0f);
            selection.render();
        }



    }
}

void maincharcontroller::toggleflying()
{
    mchar.toggleflying();
}

void maincharcontroller::togglenoclip() //hax!
{
    mchar.togglenoclip();
}

void maincharcontroller::renderdestroyblock()
{
    int32_t hoverid = tilehoverentity.getid();
    if (!tiledata::isempty(hoverid))
    {
        float hp = tilehoverentity.getcurrenthealth();
        float maxhp = tiledata::gettileinfo(hoverid).hardness;

        float destroyed = hp / maxhp;

        if (destroyed < 0.95f)
        {
            wposition wpos = tilehoverentity.getposition();
            glUniform3f(shadercontroller::getuniformid("vpos"), wpos.x, wpos.y, wpos.z);

            destructorblock[0].render();

            if (destroyed > 0.7f)
                destructorblock[0].render();
            else if (destroyed > 0.45f)
                destructorblock[1].render();
            else if (destroyed > 0.2f)
                destructorblock[2].render();
            else
                destructorblock[3].render();
        }
    }
}

void maincharcontroller::initialize()
{
    selection.initialize(1,vaocontainer::typo::LINES,3);

    selection.addvalues(0,0,0,0);selection.addvalues(0,1,0,0);
    selection.addvalues(0,1,0,0);selection.addvalues(0,1,0,1);
    selection.addvalues(0,1,0,1);selection.addvalues(0,0,0,1);
    selection.addvalues(0,0,0,1);selection.addvalues(0,0,0,0);

    selection.addvalues(0,0,0,0);selection.addvalues(0,0,1,0);
    selection.addvalues(0,1,0,0);selection.addvalues(0,1,1,0);
    selection.addvalues(0,1,0,1);selection.addvalues(0,1,1,1);
    selection.addvalues(0,0,0,1);selection.addvalues(0,0,1,1);

    selection.addvalues(0,0,1,0);selection.addvalues(0,1,1,0);
    selection.addvalues(0,1,1,0);selection.addvalues(0,1,1,1);
    selection.addvalues(0,1,1,1);selection.addvalues(0,0,1,1);
    selection.addvalues(0,0,1,1);selection.addvalues(0,0,1,0);

    selection.setvbos();

    mchar.lifeform::setstats(25.0f, 30.0f, 1.0f, 1.0f, 0.7f, 1.0f);

    for (int a = 0; a < 4; a++)
    {
        tiledata::addblock(ctilepos(0,0,0), tiledata::gettileid("t_destroy"+std::to_string(a+1)), tiledata::SHAPE_BLOCK, 255, 128, rgbcolor255(0,0,0), 0, 0, rgbcolor255(255,255,255), destructorblock[a]);
        destructorblock[a].setvbos();
    }

    mchar.fillinv();
}


wtilepos maincharcontroller::gettilehover()
{
    return tilehover;
}

wtilepos maincharcontroller::gettilehoverentityposition()
{
    return tilehoverentity.getposition();
}

direction maincharcontroller::getviewdir()
{
    return mchar.getviewdir();
}

hdirection maincharcontroller::gethviewdir()
{
    return mchar.gethviewdir();
}

wposition maincharcontroller::getmaincharposition()
{
    return mchar.getposition();
}

wposition maincharcontroller::getmaincharcamera()
{
    return mchar.geteyeposition();
}

void maincharcontroller::updatecamera()
{
    mchar.updatecamera();
}

void maincharcontroller::changeselection(int selection)
{
    mchar.actionbarselection = selection;
    utils::clamp(mchar.actionbarselection, 0, 9);

    inventory::invitem& iitem = mchar.mcharinv.getinvitem(mchar.actionbarselection);
    if (iitem.quantity > 0)
    {
        itemmanager::item& iteminfo = itemmanager::getitem(iitem.itemid);
        selectionmode = iteminfo.selectionmode;
    }

}

void maincharcontroller::changeselectiondelta(int selectiondelta)
{
    changeselection(mchar.actionbarselection+selectiondelta);
}

void maincharcontroller::useselecteditem()
{
    inventory::invitem& iitem = mchar.mcharinv.getinvitem(mchar.actionbarselection);

    if (mchar.getitemusecooldown(mchar.actionbarselection) == 0 && iitem.quantity > 0)
    {
        itemmanager::item& iteminfo = itemmanager::getitem(iitem.itemid);

        entity* user = nullptr;
        entity* target = nullptr;

        if (iteminfo.itemtype == itemtype::consumable || iteminfo.itemtype == itemtype::usable)
        {
            user = &mchar;
            target = &mchar;
        }
        if (iteminfo.itemtype == itemtype::block || iteminfo.itemtype == itemtype::placeableobject || iteminfo.itemtype == itemtype::flag)
        {
            user = &mchar;
            target = &tilehoverentity;
        }
        if (iteminfo.itemtype == itemtype::tool)
        {
            user = &mchar;
            target = &tilehoverentity; //
        }

        bool activated = false;

        for (std::shared_ptr<effect> e : iteminfo.useeffects)
        {
            activated = e->activate(user, target);
        }

        if (activated)
        {
            mchar.setitemusecooldown(mchar.actionbarselection, iteminfo.speed);

            /*if (iteminfo.itemtype == itemmanager::I_BLOCK)
            {
                mchar.usecurrentlyselecteditem(false);
                //tilehoverentity.resethealth(); //funker ikke fordi block blir updated på et senere tidspunkt
            }*/

            if ((iteminfo.itemtype == itemtype::consumable || iteminfo.itemtype == itemtype::block || iteminfo.itemtype == itemtype::placeableobject || iteminfo.itemtype == itemtype::flag))
            {
                mchar.usecurrentlyselecteditem(true);
                //iitem.quantity -= 1;
                //uiingame::updateactionbaritems(true); //litt krøkkete å ha denne her? ha heller en func i uiingame som detekterer action bar changes
            }
        }
    }
}

void maincharcontroller::update()
{
    //std::cout << "A";

    for (int a = 0; a < 10; a++)
    {
        mchar.setitemusecooldowndelta(a, -timekeeper::getcappeddeltatime());
    }

    mchar.lifeform::update();

    //std::cout << "B";

    /*glm::vec4 mdata = renderer::getmousedata();

    tileinteract = chunkcoords::wpostowtilepos(wposition(mdata.x, mdata.y, mdata.z) + (getviewdir() / 10.0f));

    if (getselectionmode() == SEL_BLOCK)
        tilehover = chunkcoords::wpostowtilepos(wposition(mdata.x, mdata.y, mdata.z) + (getviewdir() / 10.0f)); //negativ viewdir hvis lufttile skal selectes (SEL_AIR)
    else
        tilehover = chunkcoords::wpostowtilepos(wposition(mdata.x, mdata.y, mdata.z) - (getviewdir() / 10.0f));*/

    blocktracer::hitblock hit = blocktracer::traceblocks(mchar.geteyeposition(), mchar.getviewdir(), 6.0f);

    /*
    chunkpos cpos {chunkpos{0,0}};
        ctilepos ctpos {ctilepos{0,-1,0}};
        tilesideid hitside {tilesideid::xm};
    */

    if (chunkcoords::withinworld(hit.ctpos))
    {
        tilehover = wposition(hit.cpos.x * chunkwidth + hit.ctpos.x, hit.ctpos.y, hit.cpos.y * chunkwidth + hit.ctpos.z);
        tilesidehover = hit.hitside;
    }
    else
    {
        tilehover = wposition(0.0f, -1.0f, 0.0f);
    }

    //std::cout << "C";

    if (tilehover != oldtilehover)
    {
        oldtilehover = tilehover;
        //if (chunkcoords::wtileposwithinworldbounds(tilehover))
        tilehoverentity.setposition(tilehover);
    }
    if (tilesidehover != oldtilesidehover)
    {
        oldtilesidehover = tilesidehover;
        tilehoverentity.setfacingdirection(tilesidehover); //hitside
    }


    //std::cout << "D";

    movement();

    //std::cout << "E";

    updatecamera();

    //std::cout << "F\n";
}

void maincharcontroller::mcharjump()
{
    if (mchar.onfloor || mchar.flying)
    {
        mchar.vel.y = -0.3f;
    }
}

bool maincharcontroller::isunderwater()
{
    wposition mcpos = mchar.geteyeposition();
    tileid tid = chunkcontroller::gettileid(mcpos);
    if (tiledata::gettileinfo(tid).ttype == tiledata::T_WATER) return true;
    else return false;
}

bool maincharcontroller::isinwater()
{
    wposition mcpos = mchar.geteyeposition();
    mcpos.y += 1.2f;//ikkje bra
    tileid tid = chunkcontroller::gettileid(mcpos);
    if (tiledata::gettileinfo(tid).ttype == tiledata::T_WATER) return true;
    else return false;
}

void maincharcontroller::movement()
{
    //std::cout << "movement ";

    if (mchar.flying || isinwater())
    {
        if (hmovement != hdirection(0.0f, 0.0f))
        {
            hmovement = glm::normalize(hmovement);

            if (isinwater()) hmovement /= 3.0f;

            mchar.moveflying(hmovement);
        }

        /*wposition wp = mchar.getnextposition();
        mchar.setposition(wp);*/

        if (!mchar.noclip) physicsmanager::boxphysics(mchar);
        else
        {
            mchar.setposition(mchar.getnextposition());
        }

        if (mchar.flying || isunderwater())
        {
            mchar.setvelocity(velocity{0.0f,0.0f,0.0f});
        }
    }
    else
    {
        if (hmovement != hdirection(0.0f, 0.0f))
        {
            hmovement = glm::normalize(hmovement);

            mchar.movehoriz(hmovement / 6.0f);
        }

        //mchar.updateposition();
        if (!mchar.noclip) physicsmanager::boxphysics(mchar);

        //mchar.setvelocity(velocity{0.0f,0.0f,0.0f});
    }

    if (cameramoveable)
        mchar.rotateview(inputmanager::getmousedelta());

    hmovement = hdirection(0.0f,0.0f);
}
