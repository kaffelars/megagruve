#include "consts.h"
#include "scenegameinitializer.h"

#include "scenec.h"
#include "maincharcontroller.h"
#include "chunkcontroller.h"
#include "uiingame.h"
#include "uicontroller.h"
#include "settings.h"

scenegameinitializer::scenegameinitializer()
{
    //ctor
    currentstep = 0;
}

scenegameinitializer::~scenegameinitializer()
{
    //dtor
}

void scenegameinitializer::beginnewworld()
{
    maincharcontroller::resetmainchar();
    chunkcontroller::preparenewworld();
    chunkcontroller::preparestartingarea(maincharcontroller::getmainchar().getposition());
    maincharcontroller::movemainchartofloor();
    uiingame::resetui();
}

void scenegameinitializer::render()
{
    //loading box
    uielement::beginwindow("loadpepp", glm::vec2(uicontroller::getcenterx(600.0f), uicontroller::getcentery(200.0f)), glm::vec2(600, 200));

    uicontroller::changefont(uicontroller::FONT_HUGE);
    uielement::text("Loading...", glm::vec2(uicontroller::getwcenterx(ImGui::CalcTextSize("Loading...", nullptr).x, 600.0f), 25.0f));

    uielement::endwindow();
}

void scenegameinitializer::show()
{

}

void scenegameinitializer::changewindowsize()
{

}

void scenegameinitializer::hide()
{

}

void scenegameinitializer::destroy()
{

}

void scenegameinitializer::update()
{
    currentstep ++;

    if (currentstep == 4)
    {
        beginnewworld();
        scenec::changeactivescene(scenec::S_GAME);
        currentstep = 0;
    }
}

void scenegameinitializer::hiddenupdate()
{

}

void scenegameinitializer::initialize()
{

}
