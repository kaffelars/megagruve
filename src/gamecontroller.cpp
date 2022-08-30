#include "consts.h"
#include "gamecontroller.h"

namespace gamecontroller
{
    namespace
    {

    }
}


void gamecontroller::close()
{
    windowmanager::close();
    framebuffercontroller::close();
    uicontroller::destroyimgui();
}

void gamecontroller::gameloop()
{
    scenec::changeactivescene(scenec::S_MAINMENU);

    SDL_Event e;

    timekeeper::initialize();


    //THE loop
    while (!scenec::quit)
    {
        //std::cout << "loop";
        //--------- inputs og events ----------
        inputmanager::logcursorpos();//putt i refresh? neh

        windowmanager::update();

        //sdl events
        while (SDL_PollEvent(&e))
        {
            ImGui_ImplSDL2_ProcessEvent(&e);

            uint8_t winevent = 0;

            if (windowmanager::windowhasfocus() && !windowmanager::windowjustgainedfocus())
            {
                inputmanager::processevent(e); //inputs, keys og mouse og bøttons
            }

            winevent = windowmanager::processevent(e); //window events, i.e. resize, minimize, lost focus, etc

            if (e.type == SDL_QUIT)
                scenec::quitgame();

            if (winevent == 1)
            {
                scenec::getactivescene().changewindowsize();
            }
        }

        inputmanager::processheldkeys();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(windowmanager::sdlwindow);
        ImGui::NewFrame();

        if (windowmanager::windowhasfocus() && !windowmanager::windowjustgainedfocus())
        {
            //if focus
            scenec::getactivescene().update();
        }
        else
        {
            inputmanager::clearheldkeys();
            scenec::getactivescene().hiddenupdate();
        }

        render();

        timekeeper::timekeeping(); //oppdaterer fps counter og deltatime
    }


    close();//gameloop end
}

void gamecontroller::render()
{
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//black!
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, settings::getscreenx(), settings::getscreeny());
        //glEnable(GL_DEPTH_TEST);

        scenec::getactivescene().render();

        //ui
        uicontroller::render();


        SDL_GL_SwapWindow(windowmanager::sdlwindow);
}
