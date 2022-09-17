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
    wtilepos selpos = gettilehover();

    if (selpos.y != -1)
    {
        wposition vpos = wposition(selpos) - mchar.geteyeposition();

        if (settings::getisetting(settings::SET_MBOX) && getselectionmode() == SEL_BLOCK)
        {
            glUniform3f(shadercontroller::getuniformid("vpos"), vpos.x, vpos.y, vpos.z);
            glUniform3f(shadercontroller::getuniformid("rgb"), 0.8f, 0.7f, 0.7f);
            selection.render();
        }
        else if (settings::getisetting(settings::SET_BBOX) && getselectionmode() == SEL_AIR)
        {
            //vpos += sideoffsets[static_cast<int>(tilesidehover)];
            glUniform3f(shadercontroller::getuniformid("vpos"), vpos.x, vpos.y, vpos.z);
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

    for (int a = 0; a < 4; a++)
    {
        tiledata::addblock(ctilepos(0,0,0), tiledata::gettileid("t_destroy"+std::to_string(a+1)), tiledata::SHAPE_BLOCK, 255, 15, 0, 0, 0, rgbcolor255(127,127,127), destructorblock[a]);
        destructorblock[a].setvbos();
    }
}

void maincharcontroller::resetmainchar()
{
    mchar.lifeform::setstats(25.0f, 30.0f, 1.0f, 1.0f, 0.7f, 1.0f);
    mchar.setposition(wposition{16.5f, 5.0f, 16.5f});
    mchar.setvelocity(velocity{0.0f, 0.0f, 0.0f});
    mchar.clearinv();
    mchar.fillinv();
    tilehover = wtilepos(0,0,0);
    oldtilehover = wtilepos(0,0,0);

    tilesidehover = tilesideid::xm;
    oldtilesidehover = tilesideid::xm;

    hmovement = glm::vec2(0.0f);

    mcharlight = 0.0f;

    updatecamera();
}

void maincharcontroller::movemainchartofloor() //used when starting new world
{
    physicsmanager::moveboxtofloor(mchar);
}


wtilepos maincharcontroller::gettilehover()
{
    wtilepos selpos = tilehover;

    wposition vpos = wposition(selpos);// - mchar.geteyeposition();

    if (getselectionmode() == SEL_AIR)
    {
        vpos += sideoffsets[static_cast<int>(tilesidehover)];
    }
    return vpos;
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

void maincharcontroller::changeselection(int sel)
{
    mchar.actionbarselection = sel;
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

itemtype maincharcontroller::getcurrentlyselecteditemtype()
{
    inventory::invitem& iitem = mchar.mcharinv.getinvitem(mchar.actionbarselection);

    if (iitem.quantity>0)
    {
        return itemmanager::getitem(iitem.itemid).itemtype;
    }

    return itemtype::none;
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


            if ((iteminfo.itemtype == itemtype::consumable || iteminfo.itemtype == itemtype::block || iteminfo.itemtype == itemtype::placeableobject || iteminfo.itemtype == itemtype::flag))
            {
                mchar.usecurrentlyselecteditem(true);
            }
        }
    }
}

void maincharcontroller::update()
{
    for (int a = 0; a < 10; a++)
    {
        mchar.setitemusecooldowndelta(a, -timekeeper::getcappeddeltatime());
    }

    mchar.lifeform::update();


    itemtype i = getcurrentlyselecteditemtype();

    blocktracer::hitblock hit = blocktracer::traceblocks(mchar.geteyeposition(), mchar.getviewdir(), 6.0f, (i == itemtype::block || i == itemtype::placeableobject) ? true: false);



    if (chunkcoords::withinworld(hit.ctpos))
    {
        tilehover = wposition(hit.cpos.x * chunkwidth + hit.ctpos.x, hit.ctpos.y, hit.cpos.y * chunkwidth + hit.ctpos.z);
        tilesidehover = hit.hitside;
    }
    else
    {
        tilehover = wposition(0.0f, -1.0f, 0.0f);
    }

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


    movement();

    updatecamera();

    mchar.activatewalking();
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
    mcpos.y += 1.5f;//ikkje bra
    tileid tid = chunkcontroller::gettileid(mcpos);
    if (tiledata::iswater(tid)) return true;
    else return false;
}

void maincharcontroller::currentlyrunning()
{
    mchar.activaterunning();
}

void maincharcontroller::currentlysneaking()
{
    mchar.activatesneaking();
}

void maincharcontroller::movement()
{
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
