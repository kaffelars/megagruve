#include "consts.h"
#include "timekeeper.h"

namespace timekeeper
{
    std::chrono::high_resolution_clock::time_point tid[3];

    float deltatime; //frame time in ms
    int frames;
}

void timekeeper::initialize()
{
    deltatime = 16.0f;
    frames = 0;
    tid[0] = std::chrono::high_resolution_clock::now();
    tid[1] = std::chrono::high_resolution_clock::now();
    tid[2] = std::chrono::high_resolution_clock::now();
}

float timekeeper::getdeltatime()
{
    return deltatime;
}

float timekeeper::gettimefactor() //returnerer faktor i forhold til 60 fps
{
    float factor = deltatime / 16.66667f;
    if (factor > 1.0) factor = 1.0; //60 fps min
    if (factor == 0.0f) factor = 0.1f; //bøgg?
    return factor;
}

void timekeeper::timekeeping()
{
    //deltatime så ting er uavhengig av fps
    tid[2] = std::chrono::high_resolution_clock::now();
    deltatime = std::chrono::duration_cast<std::chrono::milliseconds>(tid[2] - tid[1]).count();

    frames++;

    tid[1] = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(tid[1] - tid[0]).count();



    if (duration > 1000)
    {
        int fps = frames * (1000.0f/duration);
        tid[0] = std::chrono::high_resolution_clock::now();
        frames = 0;
        std::stringstream tittel;

        tittel << "fps: " << fps;
        SDL_SetWindowTitle(windowmanager::sdlwindow, tittel.str().c_str());
    }
}
