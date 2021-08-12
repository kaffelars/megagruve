#ifndef SCENE_H
#define SCENE_H

//#include "uicontroller.h"
#include "shadercontroller.h"
#include "framebuffercontroller.h"

class scene
{
    public:
        scene();
        virtual ~scene();

        virtual void initialize() =0;//run first upon le start
        virtual void show() =0;//run once when scene is changed to
        virtual void hide() =0;//run once when scene is changed from
        virtual void destroy() =0;//run once when scene is destroyed

        //each frame, update->render

        virtual void render() =0;//setting up to render stuff, incl ui, runs every frame
        virtual void update() =0;//updates scene - *only run when window focus*
    protected:
    private:
};

#endif // SCENE_H
