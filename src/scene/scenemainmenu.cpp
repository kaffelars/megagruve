#include "consts.h"
#include "scenemainmenu.h"

#include "settings.h"
#include "utils.h"
#include "texturemanager.h"
#include "windowmanager.h"
#include "randfunc.h"

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
    recreatebackground();
}

void scenemainmenu::recreatebackground()
{
    bgimage.cleanvbos();
    bgimage.initialize(2, vaocontainer::typo::TRIANGLES, 4, 4);

    int grass = texturemanager::gettiletexturenumber("grass");
    int grass2 = texturemanager::gettiletexturenumber("grass2");
    int grassside = texturemanager::gettiletexturenumber("grass_side_overlay");
    int dirt = texturemanager::gettiletexturenumber("dirt");

    int toptex;
    int sidetex1;
    int sidetex2;
    bool grassoverlay = true;

    float nocolor = utils::packu2f(255, 255, 255);
    float grasscolor = utils::packu2f(88, 250, 88);
    float topcolor = grasscolor;

    float scalex = 0.12f;
    float scaley = 0.12f * windowmanager::windowaspectratio();
    int exs = (1.0f / scalex) * 1.5f;
    int eys = (1.0f / scaley) * 1.5f;

    float wx = scalex / 2.0f;
    float wy = scaley / 4.0f;
    float wyy = scaley / 8.0f;

    float scalert = 1.5f;

    std::vector<glm::vec3> drawflowers;

    for (int x = -exs; x <= exs; x++)
    {
        int offse = 0;

        for (int y = -eys*2; y <= eys*2; y++)
        {
            float ex = float(x) * scalex;;

            if (offse % 2 == 1)
            {
                ex += wx;
            }
            offse++;

            float ey = float(y) * scaley / scalert;

            //std::cout << ex << " - " << ey << "\n";

            toptex = grass;
            sidetex1 = dirt;
            sidetex2 = dirt;
            grassoverlay = true;
            topcolor = grasscolor;

            float rando = randfunc::noise(ex, ey, 2.61f);

            if (rando > 0.86f)
            {
                if (rando > 0.98f)
                    toptex = texturemanager::gettiletexturenumber("diamond_ore");
                else
                    toptex = texturemanager::gettiletexturenumber("rock");

                sidetex1 = toptex;
                sidetex2 = toptex;
                grassoverlay = false;
                topcolor = nocolor;
            }
            if (rando > 0.29f && rando < 0.36f)
            {
                toptex = texturemanager::gettiletexturenumber("clay");
                sidetex1 = toptex;
                sidetex2 = toptex;
                grassoverlay = false;
                topcolor = nocolor;
            }
            if (rando > 0.45 && rando < 0.59)
            {
                toptex = texturemanager::gettiletexturenumber("dirt");
                sidetex1 = toptex;
                sidetex2 = toptex;
                grassoverlay = false;
                topcolor = nocolor;
            }
            if (rando < -0.4f && rando > -0.5f)
            {
                toptex = grass2;
            }
            if (rando < -0.86f)
            {
                if (rando < -0.95f)
                    toptex = texturemanager::gettiletexturenumber("coal_ore");
                else
                    toptex = texturemanager::gettiletexturenumber("rock");

                sidetex1 = toptex;
                sidetex2 = toptex;
                grassoverlay = false;
                topcolor = nocolor;
            }
            if (rando < -0.16f && rando > -0.19f)
            {
                toptex = texturemanager::gettiletexturenumber("planks");
                sidetex1 = texturemanager::gettiletexturenumber("bookcase");
                sidetex2 = sidetex1;
                grassoverlay = false;
                topcolor = nocolor;
            }
            if (rando < -0.26f && rando > -0.30f)
            {
                toptex = texturemanager::gettiletexturenumber("bedrock");
                sidetex1 = toptex;
                sidetex2 = sidetex1;
                grassoverlay = false;
                topcolor = nocolor;
            }

            //top
            bgimage.addvalues(0, ex, ey + wyy, 0, toptex);
            bgimage.addvalues(0, ex + wx, ey, 0, toptex);
            bgimage.addvalues(0, ex + scalex, ey + wyy, 0, toptex);

            bgimage.addvalues(0, ex, ey + wyy, 0, toptex);
            bgimage.addvalues(0, ex + scalex, ey + wyy, 0, toptex);
            bgimage.addvalues(0, ex + wx, ey + wy, 0, toptex);

            bgimage.addvalues(1, 0   , 0   , 1.0f, topcolor);
            bgimage.addvalues(1, 1.0f, 0   , 1.0f, topcolor);
            bgimage.addvalues(1, 1.0f, 1.0f, 1.0f, topcolor);

            bgimage.addvalues(1, 0.0f, 0   , 1.0f, topcolor);
            bgimage.addvalues(1, 1.0f, 1.0f, 1.0f, topcolor);
            bgimage.addvalues(1, 0   , 1.0f, 1.0f, topcolor);

            //right
            bgimage.addvalues(0, ex + wx, ey+wy+wyy/scalert - scaley + wyy, 0, sidetex1);
            bgimage.addvalues(0, ex + scalex, ey+wy+wyy/scalert - scaley+wy, 0, sidetex1);
            bgimage.addvalues(0, ex + wx, ey, 0, sidetex1);

            bgimage.addvalues(0, ex + scalex, ey+wy+wyy/scalert - scaley + wy, 0, sidetex1);
            bgimage.addvalues(0, ex + scalex, ey+wy - wyy, 0, sidetex1);
            bgimage.addvalues(0, ex + wx, ey, 0, sidetex1);

            float ligt = 0.8f;

            bgimage.addvalues(1, 0   , 1.0f, ligt, nocolor);
            bgimage.addvalues(1, 1.0f, 1.0f, ligt, nocolor);
            bgimage.addvalues(1, 0.0f, 0.0f, ligt, nocolor);

            bgimage.addvalues(1, 1.0f, 1.0f, ligt, nocolor);
            bgimage.addvalues(1, 1.0f, 0.0f, ligt, nocolor);
            bgimage.addvalues(1, 0   , 0.0f, ligt, nocolor);

            if (grassoverlay)
            {
                bgimage.addvalues(0, ex + wx, ey+wy+wyy/scalert - scaley + wyy, 0, grassside);
                bgimage.addvalues(0, ex + scalex, ey+wy+wyy/scalert - scaley+wy, 0, grassside);
                bgimage.addvalues(0, ex + wx, ey, 0, grassside);

                bgimage.addvalues(0, ex + scalex, ey+wy+wyy/scalert - scaley + wy, 0, grassside);
                bgimage.addvalues(0, ex + scalex, ey+wy - wyy, 0, grassside);
                bgimage.addvalues(0, ex + wx, ey, 0, grassside);

                bgimage.addvalues(1, 0   , 1.0f, ligt, grasscolor);
                bgimage.addvalues(1, 1.0f, 1.0f, ligt, grasscolor);
                bgimage.addvalues(1, 0.0f, 0.0f, ligt, grasscolor);

                bgimage.addvalues(1, 1.0f, 1.0f, ligt, grasscolor);
                bgimage.addvalues(1, 1.0f, 0.0f, ligt, grasscolor);
                bgimage.addvalues(1, 0   , 0.0f, ligt, grasscolor);
            }

            //left
            bgimage.addvalues(0, ex, ey+wy+wyy/scalert - scaley + wy, 0, sidetex2);
            bgimage.addvalues(0, ex + wx, ey+wy+wyy/scalert - scaley + wyy, 0, sidetex2);
            bgimage.addvalues(0, ex, ey+wy - wyy, 0, sidetex2);

            bgimage.addvalues(0, ex + wx, ey+wy+wyy/scalert - scaley + wyy, 0, sidetex2);
            bgimage.addvalues(0, ex + wx, ey, 0, sidetex2);
            bgimage.addvalues(0, ex, ey+wy - wyy, 0, sidetex2);

            ligt = 0.6f;

            bgimage.addvalues(1, 0   , 1.0f, ligt, nocolor);
            bgimage.addvalues(1, 1.0f, 1.0f, ligt, nocolor);
            bgimage.addvalues(1, 0.0f, 0.0f, ligt, nocolor);

            bgimage.addvalues(1, 1.0f, 1.0f, ligt, nocolor);
            bgimage.addvalues(1, 1.0f, 0.0f, ligt, nocolor);
            bgimage.addvalues(1, 0   , 0.0f, ligt, nocolor);

            if (grassoverlay)
            {
                bgimage.addvalues(0, ex, ey+wy+wyy/scalert - scaley + wy, 0, grassside);
                bgimage.addvalues(0, ex + wx, ey+wy+wyy/scalert - scaley + wyy, 0, grassside);
                bgimage.addvalues(0, ex, ey+wy - wyy, 0, grassside);

                bgimage.addvalues(0, ex + wx, ey+wy+wyy/scalert - scaley + wyy, 0, grassside);
                bgimage.addvalues(0, ex + wx, ey, 0, grassside);
                bgimage.addvalues(0, ex, ey+wy - wyy, 0, grassside);

                bgimage.addvalues(1, 0   , 1.0f, ligt, grasscolor);
                bgimage.addvalues(1, 1.0f, 1.0f, ligt, grasscolor);
                bgimage.addvalues(1, 0.0f, 0.0f, ligt, grasscolor);

                bgimage.addvalues(1, 1.0f, 1.0f, ligt, grasscolor);
                bgimage.addvalues(1, 1.0f, 0.0f, ligt, grasscolor);
                bgimage.addvalues(1, 0   , 0.0f, ligt, grasscolor);
            }


            if (grassoverlay)//flowers
            {
                float fando = randfunc::noise(ex + 3249, ey+1216, 1.11f);
                if (fando > 0.2f)
                {
                    drawflowers.push_back(glm::vec3(ex, ey, fando));
                }
            }
        }
    }

    for (glm::vec3 f: drawflowers)
    {
        float colortint = nocolor;

        if (f.z < 0.35f)
            toptex = texturemanager::gettiletexturenumber("grasstuft1");
        else if (f.z < 0.5f)
            toptex = texturemanager::gettiletexturenumber("grasstuft2");
        else if (f.z < 0.66f)
            toptex = texturemanager::gettiletexturenumber("flower1");
        else if (f.z < 0.83)
            toptex = texturemanager::gettiletexturenumber("flower2");
        else
            toptex = texturemanager::gettiletexturenumber("flower3");

        if (f.z < 0.5f) colortint = grasscolor;

        float ex = f.x;
        float ey = f.y;
        float ligt = 1.0f;

        bgimage.addvalues(0, ex + wx/2          , ey + wyy, 0, toptex);
        bgimage.addvalues(0, ex + scalex - wx/2 , ey + wyy + wy*2, 0, toptex);
        bgimage.addvalues(0, ex + wx/2          , ey + wyy + wy*2, 0, toptex);

        bgimage.addvalues(0, ex + wx/2          , ey + wyy, 0, toptex);
        bgimage.addvalues(0, ex + scalex - wx/2 , ey + wyy, 0, toptex);
        bgimage.addvalues(0, ex + scalex - wx/2 , ey + wyy + wy*2, 0, toptex);

        bgimage.addvalues(1, 0   , 1.0f, ligt, colortint);
        bgimage.addvalues(1, 1.0f, 0.0f, ligt, colortint);
        bgimage.addvalues(1, 0.0f, 0.0f, ligt, colortint);

        bgimage.addvalues(1, 0.0f, 1.0f, ligt, colortint);
        bgimage.addvalues(1, 1.0f, 1.0f, ligt, colortint);
        bgimage.addvalues(1, 1.0f, 0.0f, ligt, colortint);
    }

    bgimage.setvbos();
}

void scenemainmenu::show()
{

}

void scenemainmenu::changewindowsize()
{
    recreatebackground();
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
    glDisable(GL_STENCIL_TEST);
    glDisable (GL_CULL_FACE);
    glViewport(0, 0, settings::getisetting(settings::SET_SCREENX), settings::getisetting(settings::SET_SCREENY));

    shadercontroller::activateshader(shadercontroller::SH_MENU);
    glUniform1i(shadercontroller::getuniformid("tex"), 0);
    //texturemanager::bindiconstexture(texturemanager::ICONS_MEDIUM, 0);
    texturemanager::bindtiletextures(0);

    bgimage.render();

    //main menu
    uielement::beginwindow("peppe", glm::vec2(uicontroller::getcenterx(600.0f), 0.0f), glm::vec2(600, settings::getscreeny()));

    uicontroller::changefont(uicontroller::FONT_HUGE);
    uielement::text("Megagruve", glm::vec2(uicontroller::getwcenterx(ImGui::CalcTextSize("Megagruve", nullptr).x, 600.0f), 3.0f));

    uicontroller::changefont(uicontroller::FONT_NORMAL);

    float centerx = uicontroller::getwcenterx(300.0f, 600.0f);



    if (uielement::button("start new game", glm::vec2(centerx, 200.0f), glm::vec2(300.0f, 50.0f)))
    {
        scenec::changeactivescene(scenec::S_GAMEINITIALIZER);
    }

    int seed = randfunc::getseed();
    uielement::text("Set generator seed:", glm::vec2(uicontroller::getwcenterx(ImGui::CalcTextSize("Set generator seed:", nullptr).x, 600.0f), uicontroller::ypos(260.0f)));
    uielement::setcursorpos(centerx - 40.0f, 280.0f);
    if (uielement::sliderint(0, 10000, seed, 1))
    {
        randfunc::setseed(seed);
        recreatebackground();
    }

    int changeseed = 0;

    if (uielement::button("-10", glm::vec2(220.0f, 320.0f), glm::vec2(30.0f, 30.0f))) changeseed -= 10;
    if (uielement::button("-1", glm::vec2(260.0f, 320.0f), glm::vec2(30.0f, 30.0f))) changeseed -= 1;
    if (uielement::button("+1", glm::vec2(300.0f, 320.0f), glm::vec2(30.0f, 30.0f))) changeseed += 1;
    if (uielement::button("+10", glm::vec2(340.0f, 320.0f), glm::vec2(30.0f, 30.0f))) changeseed += 10;

    if (changeseed && seed+changeseed > 0 && seed+changeseed <= 10000) randfunc::setseed(seed+changeseed);

    if (uielement::button("settings", glm::vec2(centerx, 470.0f), glm::vec2(300.0f, 50.0f))) scenec::changeactivescene(scenec::S_SETTINGS);
    if (uielement::button("quit", glm::vec2(centerx, 750.0f), glm::vec2(300.0f, 50.0f))) scenec::quitgame();

    uielement::text("github.com/kaffelars/megagruve", glm::vec2(uicontroller::getwcenterx(ImGui::CalcTextSize("github.com/kaffelars/megagruve", nullptr).x, 600.0f), uicontroller::ypos(-40.0f)));

    uielement::endwindow();
}

void scenemainmenu::update()
{

}

void scenemainmenu::hiddenupdate()
{

}

void scenemainmenu::destroy()
{

}
