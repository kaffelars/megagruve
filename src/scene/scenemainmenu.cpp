#include "consts.h"
#include "scenemainmenu.h"

scenemainmenu::scenemainmenu()
{
    //ctor
}

scenemainmenu::~scenemainmenu()
{
    //dtor
}

void scenemainmenu::initialize()
{

}

void scenemainmenu::show()
{

}

void scenemainmenu::hide()
{

}

void scenemainmenu::render()
{
    //main menu
    uielement::beginwindow("peppe", glm::vec2(uicontroller::getcenterx(600.0f), 0.0f), glm::vec2(600, settings::getscreeny()));

    uicontroller::changefont(uicontroller::FONT_LARGE);
    uielement::text("Megagruve", glm::vec2(uicontroller::getwcenterx(ImGui::CalcTextSize("Megagruve", nullptr).x, 600.0f), 3.0f));

    uicontroller::changefont(uicontroller::FONT_NORMAL);

    float centerx = uicontroller::getwcenterx(300.0f, 600.0f);


    if (uielement::button("start game", glm::vec2(centerx, 200.0f), glm::vec2(300.0f, 50.0f))) scenec::changeactivescene(scenec::S_GAME);
    if (uielement::button("settings", glm::vec2(centerx, 470.0f), glm::vec2(300.0f, 50.0f))) scenec::changeactivescene(scenec::S_SETTINGS);
    if (uielement::button("quit", glm::vec2(centerx, 750.0f), glm::vec2(300.0f, 50.0f))) scenec::quitgame();

    uielement::text("Megagruve is (c) Zymbo Zoftware 2021", glm::vec2(uicontroller::getwcenterx(ImGui::CalcTextSize("Megagruve is (c) Zymbo Zoftware 2021", nullptr).x, 600.0f), uicontroller::ypos(-40.0f)));

    uielement::endwindow();
}

void scenemainmenu::update()
{

}

void scenemainmenu::destroy()
{

}
