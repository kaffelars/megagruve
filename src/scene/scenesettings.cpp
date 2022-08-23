#include "consts.h"
#include "scenesettings.h"

scenesettings::scenesettings()
{
    //ctor
}

scenesettings::~scenesettings()
{
    //dtor
}

void scenesettings::initialize()
{
    waitingforkeypress = -1;

    curselect = 0;
}

void scenesettings::show()
{
    goback = false;
}

void scenesettings::hide()
{

}

void scenesettings::render()
{
    std::string selections[5] = {"Game", "Video", "Keybinds"};

    //settings
    uielement::beginwindow("peppe", glm::vec2(0.0f, 0.0f), glm::vec2(settings::getscreenx(), settings::getscreeny()), false, false);

    uicontroller::changefont(uicontroller::FONT_LARGE);
    uielement::text(selections[curselect].c_str(), glm::vec2(45.0f, 1.0f));

    uicontroller::changefont(uicontroller::FONT_NORMAL);

    int tempselect = curselect;

    for (int a = 0; a < 3; a++)
    {
        if (a == curselect)
        {
            //uicontroller::text(selections[a].c_str(), glm::vec2(1.5f, 5.5f + (a*10.0f)));
            uielement::button(selections[curselect].c_str(), glm::vec2(25.0f, 130.0f + (a*75.0f)), glm::vec2(300.0f, 50.0f), true);
        }
        else
        {
            if (uielement::button(selections[a].c_str(), glm::vec2(25.0f, 130.0f + (a*75.0f)), glm::vec2(300.0f, 50.0f))) tempselect = a;
        }
    }

    curselect = tempselect;

    if (uielement::button("back", glm::vec2(25.0f, uicontroller::ypos(-75.0f)), glm::vec2(300.0f, 50.0f))) scenec::returntopreviousscene();

    uielement::setcursorpos(350, 130);

    ImGui::BeginChild("heks", ImVec2(settings::getscreenx() - 400, settings::getscreeny()-155.0f), true);

    if (curselect == 0) game();
    if (curselect == 1) video();
    if (curselect == 2) keybinds();

    ImGui::EndChild();

    uielement::endwindow();
}

void scenesettings::game()
{
    uielement::text("Render block placement helper box: ", glm::vec2(65.0f, 25.0f));
    bool bbox = settings::getisetting(settings::SET_BBOX);
    if (uielement::checkbox(bbox, glm::vec2(20.0f, 25.0f))) settings::setisetting(settings::SET_BBOX, bbox);

    uielement::text("Render mining helper box: ", glm::vec2(65.0f, 55.0f));
    bbox = settings::getisetting(settings::SET_MBOX);
    if (uielement::checkbox(bbox, glm::vec2(20.0f, 55.0f))) settings::setisetting(settings::SET_MBOX, bbox);

    uielement::text("Max threads (in addition to main thread): ", glm::vec2(25.0f, 95.0f));
    int maxt = settings::getisetting(settings::SET_MAXTHREADS);
    uielement::setposition(25.0f, 115.0f);
    if (uielement::sliderint(1, 32, maxt, 1)) settings::setisetting(settings::SET_MAXTHREADS, maxt);

    uielement::text("Mouse sensitivity: ", glm::vec2(25.0f, 155.0f));
    maxt = settings::getisetting(settings::SET_MOUSESENS);
    uielement::setposition(25.0f, 175.0f);
    if (uielement::sliderint(1, 100, maxt, 1)) settings::setisetting(settings::SET_MOUSESENS, maxt);
}

void scenesettings::video()
{
    uielement::text("Render distance: ", glm::vec2(25.0f, 25.0f));
    int renderdist = settings::getisetting(settings::SET_CDIST);
    uielement::setposition(100.0f, 25.0f);
    if (uielement::sliderint(5, 32, renderdist, 1)) settings::setisetting(settings::SET_CDIST, renderdist);

    uielement::text("Vsync: ", glm::vec2(25.0f, 95.0f));
    bool vsync = settings::getisetting(settings::SET_VSYNC);
    uielement::checkbox(vsync, glm::vec2(90.0f, 95.0f));
    if (vsync != settings::getisetting(settings::SET_VSYNC))
    {
        settings::setisetting(settings::SET_VSYNC, vsync);
        windowmanager::setvsync(vsync);
    }

    uielement::text("UI scale: ", glm::vec2(25.0f, 125.0f));
    int uiscale = 10.0f * settings::getfsetting(settings::SET_UISCALE);
    uielement::setposition(100.0f, 125.0f);
    uielement::sliderint(5, 30, uiscale, 1);
    float uisc = (float)uiscale / 10.0f;
    if (uisc != settings::getfsetting(settings::SET_UISCALE))
    {
        settings::setfsetting(settings::SET_UISCALE, uisc);
    }
}

void scenesettings::keybinds()
{
    float index = 0.0f;




    /*for (inputmanager::b_key b : inputmanager::bound_keys)
    {
        uielement::text(b.key_function.c_str(), glm::vec2(25.0f, 25.0f + index * 30.0f));

        uielement::text(inputmanager::getkeyname(b), glm::vec2(250.0f, 25.0f + index * 30.0f));
        if (waitingforkeypress == -1)
        {
            if (uielement::button("rebind##"+std::to_string(index), glm::vec2(450.0f, 25.0f + index * 30.0f), glm::vec2(70.0f, 25.0f)))
            {
                waitingforkeypress = index;
                inputmanager::recordnextpress();
            }
        }
        else
        {
            if (waitingforkeypress == index)
            {
                uielement::text("waiting", glm::vec2(450.0f, 25.0f + index * 30.0f));
            }
        }

        index ++;
    }

    if (inputmanager::recordpress == 2)
    {
        inputmanager::recordpress = 0;
        inputmanager::bound_keys[waitingforkeypress].ktype = inputmanager::recordedpress.ktype; //shady
        inputmanager::bound_keys[waitingforkeypress].key_modifiers = inputmanager::recordedpress.key_modifiers;

        if (inputmanager::recordedpress.ktype == inputmanager::KEYTYPE_KEYBOARD) inputmanager::bound_keys[waitingforkeypress].key = inputmanager::recordedpress.key;
        else inputmanager::bound_keys[waitingforkeypress].mouse = inputmanager::recordedpress.mouse;

        waitingforkeypress = -1;
    }*/

}

void scenesettings::update()
{

}

void scenesettings::changewindowsize()
{

}

void scenesettings::hiddenupdate()
{

}

void scenesettings::destroy()
{

}
