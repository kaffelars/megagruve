#ifndef SCENEMAINMENU_H
#define SCENEMAINMENU_H

#include "scene.h"

#include "inputmanager.h"
#include "shadercontroller.h"
#include "framebuffercontroller.h"
#include "scenec.h"

#include "uicontroller.h"
#include "vaocontainer.h"

class scenemainmenu : public scene
{
    public:
        scenemainmenu();
        virtual ~scenemainmenu();

        void render();
        void show();
        void hide();
        void destroy();
        void changewindowsize();
        void recreatebackground();

        void update();
        void hiddenupdate();
        void initialize();
    protected:

    private:
        vaocontainer bgimage;
};

#endif // SCENEMAINMENU_H
