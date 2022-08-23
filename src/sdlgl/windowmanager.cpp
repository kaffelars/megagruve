#include "consts.h"
#include "windowmanager.h"


namespace windowmanager
{
    namespace
    {
        bool window_focus = true;
    }

    bool window_focus = true;
    SDL_Window* sdlwindow = nullptr;
    SDL_Renderer* sdlrenderer = nullptr;
    SDL_GLContext sdlglcontext = nullptr;
}

void windowmanager::reinitialize()
{
    //er dette trygt?

    close();
    initialize();
}

bool windowmanager::setupgamewindow()
{
    //starting sdl game window
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to init SDL\r\n";
        return false;
    }

    windowmanager::sdlwindow = SDL_CreateWindow("dummy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, settings::getisetting(settings::SET_SCREENX), settings::getisetting(settings::SET_SCREENY), SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    if (!windowmanager::sdlwindow )
    {
        std::cout << "Unable to create window\r\n";
        return false;
    }

    return true;
}

bool windowmanager::setupopengl()
{
    //initializing opengl-sdl

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);//4.5 for compute shader

    //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    windowmanager::sdlglcontext = SDL_GL_CreateContext(windowmanager::sdlwindow);

    SDL_GL_MakeCurrent(windowmanager::sdlwindow, windowmanager::sdlglcontext);

    if (!windowmanager::sdlglcontext)
    {
        std::cout << "Unable to create opengl context\r\n";
        return false;
    }


    //SDL_GL_SetSwapInterval(1);//vsync

    setvsync(settings::getisetting(settings::SET_VSYNC));

    // Init GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    glLineWidth(2.0f);

    glDisable(GL_BLEND);
    //glEnable(GL_BLEND); //blir noe rart med pos gbuf
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glDisable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);

    //glDepthFunc(GL_LEQUAL);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_PROGRAM_POINT_SIZE);

    glEnable (GL_CULL_FACE); // cull face //disable for billboards??
    glCullFace (GL_BACK); // cull back face
    glFrontFace (GL_CCW); //ccw er standard

    return true;
}

void windowmanager::initialize()
{
    if (setupgamewindow())
        std::cout << "game window setup-ed!\n";
    else
        std::cout << "noe er galt med game window\n";

    if (setupopengl())
        std::cout << "opengl setup!\n";
    else
        std::cout << "opengl failure, gg\n";
}

void windowmanager::close()
{
    SDL_DestroyRenderer(windowmanager::sdlrenderer);
	SDL_DestroyWindow(windowmanager::sdlwindow);
	SDL_GL_DeleteContext(windowmanager::sdlglcontext);

	SDL_Quit();
}

float windowmanager::windowaspectratio()
{
    return (float)settings::getscreenx() / (float)settings::getscreeny();
}

bool windowmanager::windowhasfocus()
{
    return windowmanager::window_focus;
}

void windowmanager::resizewindow(int sx, int sy)
{
    //do stuff?
    settings::setisetting(settings::SET_SCREENX, sx);
    settings::setisetting(settings::SET_SCREENY, sy);

    camera::updateperspective();

    framebuffercontroller::resizebuffers();
}

void windowmanager::setvsync(bool on)
{
    SDL_GL_SetSwapInterval(on);
}

uint8_t windowmanager::processevent(SDL_Event& e)
{
    if (e.type == SDL_WINDOWEVENT)
    {
        switch (e.window.event)
        {
            case SDL_WINDOWEVENT_RESIZED:
                resizewindow(e.window.data1, e.window.data2); return 1; break;
            case SDL_WINDOWEVENT_MINIMIZED:
                windowmanager::window_focus = false; return 2; break;
            case SDL_WINDOWEVENT_RESTORED:
                windowmanager::window_focus = true; return 3; break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                windowmanager::window_focus = false; return 4; break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                windowmanager::window_focus = true; return 5; break;

        }
    }

    return 0;
}
