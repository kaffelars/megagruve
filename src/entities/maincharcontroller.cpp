#include "consts.h"
#include "maincharcontroller.h"

#include "mainchar.h"
#include "inputmanager.h"
#include "utils.h"
#include "renderer.h"
#include "chunkcontroller.h"

namespace maincharcontroller
{
    mainchar mchar;
    bool flying = true;
    wtilepos tilehover = wtilepos(0,0,0);
    wtilepos oldtilehover = wtilepos(0,0,0);
    vaocontainer selection;
    smode selectionmode = SEL_BLOCK;

    int32_t actionbarselection = 0;

    //blockentity tilehoverentity;
}

inventory& maincharcontroller::getmcharinventory()
{
    return mchar.mcharinv;
}

int32_t maincharcontroller::getcurrenthealth()
{
    return mchar.evitals.hp;
}
int32_t maincharcontroller::getmaxhealth()
{
    return mchar.evitals.maxhp;
}

int32_t maincharcontroller::getactionbarselection()
{
    return actionbarselection;
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

    if (selpos.y != 0)
    {
        glUniform3f(shadercontroller::getuniformid("vpos"), selpos.x, selpos.y, selpos.z);
        if (getselectionmode() == SEL_BLOCK)
            glUniform3f(shadercontroller::getuniformid("rgb"), 0.8f, 0.7f, 0.7f);
        else
            glUniform3f(shadercontroller::getuniformid("rgb"), 0.8f, 0.8f, 1.0f);

        selection.render();
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

    mchar.fillinv();
}

void maincharcontroller::toggleflying()
{
    flying = !flying;
}

wtilepos maincharcontroller::gettilehover()
{
    return tilehover;
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
    return mchar.pobject.getposition();
}

void maincharcontroller::updatecamera()
{
    mchar.updatecamera();
}

void maincharcontroller::inputactions()
{
    glm::vec4 mdata = renderer::getmousedata();
    if (getselectionmode() == SEL_BLOCK)
        tilehover = chunkcontroller::wpostowtilepos(wposition(mdata.x, mdata.y, mdata.z) + (getviewdir() / 10.0f)); //negativ viewdir hvis lufttile skal selectes (SEL_AIR)
    else
        tilehover = chunkcontroller::wpostowtilepos(wposition(mdata.x, mdata.y, mdata.z) - (getviewdir() / 10.0f));
    //tilehover = wposition(mdata.x, mdata.y, mdata.z)+ (getviewdir() / 10.0f);

    if (tilehover != oldtilehover)
    {
        //hvis hover over ny tile
        oldtilehover = tilehover;

        //tilehoverentity = blockentity()
    }

    if (inputmanager::waskeyclicked(inputmanager::KEY_SELECT))
    {
        chunkcontroller::addtiletochange(tilehover, tiledata::gettileid("t_flag"));
    }

    if (inputmanager::waskeyclicked(inputmanager::KEY_MISC))
    {
        if (getselectionmode() == SEL_BLOCK)
            setselectionmode(SEL_AIR);
        else
            setselectionmode(SEL_BLOCK);
    }

    if (inputmanager::waskeyclicked(inputmanager::KEY_ZOOMIN)) actionbarselection --;
    if (inputmanager::waskeyclicked(inputmanager::KEY_ZOOMOUT)) actionbarselection ++;
    utils::clamp(actionbarselection, 0, 9);
}

void maincharcontroller::movement()
{
    hdirection hmovement = glm::vec2(0.0f);

    if (inputmanager::iskeyheld(inputmanager::KEY_LEFT)) hmovement.x += 1.0f;
    if (inputmanager::iskeyheld(inputmanager::KEY_RIGHT)) hmovement.x -= 1.0f;
    if (inputmanager::iskeyheld(inputmanager::KEY_UP)) hmovement.y += 1.0f;//z
    if (inputmanager::iskeyheld(inputmanager::KEY_DOWN)) hmovement.y -= 1.0f;//z

    if (flying)
        mchar.moveflying(hmovement);
    else
        mchar.movehoriz(hmovement);

    mchar.pobject.updateposition();

    mchar.rotateview(inputmanager::getmousedelta());
}
