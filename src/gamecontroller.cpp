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

        //sdl events
        while (SDL_PollEvent(&e))
        {
            ImGui_ImplSDL2_ProcessEvent(&e);

            inputmanager::processevent(e); //inputs, keys og mouse og bøttons
            windowmanager::processevent(e); //window events, i.e. resize, minimize, lost focus, etc

            if (e.type == SDL_QUIT)
                scenec::quitgame();
        }

        //std::cout << "lo2";

        inputmanager::processheldkeys();

        //std::cout << "lo3";

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(windowmanager::sdlwindow);
        ImGui::NewFrame();

        //std::cout << "lo§";

        if (windowmanager::windowhasfocus())
        {
            //if focus
            scenec::getactivescene().update();
        }

        //std::cout << "lo4";

        render();

        //std::cout << "lo5";

        timekeeper::timekeeping(); //oppdaterer fps counter og deltatime

        //std::cout << "lF\n";
    }


    close();//gameloop end
}



void gamecontroller::render()
{
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);//purpz!
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, settings::getscreenx(), settings::getscreeny());
        //glEnable(GL_DEPTH_TEST);

        scenec::getactivescene().render();

        //ui
        uicontroller::render();


        SDL_GL_SwapWindow(windowmanager::sdlwindow);
}
