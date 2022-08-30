#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "settings.h"
#include "framebuffercontroller.h"
#include "camera.h"

namespace windowmanager
{
    void resizewindow(int sx, int sy);
    bool windowhasfocus();
    float windowaspectratio();

    extern SDL_Window* sdlwindow;
    extern SDL_Renderer* sdlrenderer;
    extern SDL_GLContext sdlglcontext;

    bool setupgamewindow();
    bool setupopengl();
    void close();
    void update();
    bool windowjustgainedfocus();

    void setvsync(bool on);

    void reinitialize();

    void initialize();

    uint8_t processevent(SDL_Event& e);

};

#endif // WINDOWMANAGER_H
