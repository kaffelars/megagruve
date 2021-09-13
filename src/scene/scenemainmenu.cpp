#include "consts.h"
#include "scenemainmenu.h"

#include "settings.h"
#include "utils.h"

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
    bgicons.cleanvbos();
    bgicons.initialize(1, vaocontainer::typo::POINTS, 4);

    for (int a= 1; a < 101; a++)
    {
        wposition pp;
        pp.x = utils::randint(-1000, 1000);
        pp.y = utils::randint(-1000, 1000);
        float sizoz = utils::randint(64, 128);
        pp.x /= 1000.0f;
        pp.y /= 1000.0f;
        bgicons.addvalues(0, pp.x, pp.y, a, sizoz);
    }

    bgicons.setvbos();
}

void scenemainmenu::show()
{

}

void scenemainmenu::hide()
{

}

void scenemainmenu::render()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, settings::getisetting(settings::SET_SCREENX), settings::getisetting(settings::SET_SCREENY));

    shadercontroller::activateshader(shadercontroller::SH_SIMPLEPARTICLE);
    texturemanager::bindiconstexture(texturemanager::ICONS_MEDIUM, 0);

    bgicons.render();

    //main menu
    uielement::beginwindow("peppe", glm::vec2(uicontroller::getcenterx(600.0f), 0.0f), glm::vec2(600, settings::getscreeny()));

    uicontroller::changefont(uicontroller::FONT_HUGE);
    uielement::text("Megagruve", glm::vec2(uicontroller::getwcenterx(ImGui::CalcTextSize("Megagruve", nullptr).x, 600.0f), 3.0f));

    uicontroller::changefont(uicontroller::FONT_NORMAL);

    float centerx = uicontroller::getwcenterx(300.0f, 600.0f);


    if (uielement::button("start game", glm::vec2(centerx, 200.0f), glm::vec2(300.0f, 50.0f))) scenec::changeactivescene(scenec::S_GAME);
    if (uielement::button("settings", glm::vec2(centerx, 470.0f), glm::vec2(300.0f, 50.0f))) scenec::changeactivescene(scenec::S_SETTINGS);
    if (uielement::button("quit", glm::vec2(centerx, 750.0f), glm::vec2(300.0f, 50.0f))) scenec::quitgame();

    uielement::text("github.com/kaffelars/megagruve", glm::vec2(uicontroller::getwcenterx(ImGui::CalcTextSize("github.com/kaffelars/megagruve", nullptr).x, 600.0f), uicontroller::ypos(-40.0f)));

    uielement::endwindow();
}

void scenemainmenu::update()
{

}

void scenemainmenu::destroy()
{

}
