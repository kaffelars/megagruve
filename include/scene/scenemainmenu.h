#ifndef SCENEMAINMENU_H
#define SCENEMAINMENU_H

#include "scene.h"

#include "inputmanager.h"
#include "shadercontroller.h"
#include "framebuffercontroller.h"
#include "scenec.h"

#include "uicontroller.h"

class scenemainmenu : public scene
{
    public:
        scenemainmenu();
        virtual ~scenemainmenu();

        void render();
        void show();
        void hide();
        void destroy();

        void update();
        void initialize();
    protected:

    private:
};

#endif // SCENEMAINMENU_H
