#ifndef SCENEGAME_H
#define SCENEGAME_H

#include "scene.h"
#include "renderer.h"
#include "maincharcontroller.h"
#include "chunkcontroller.h"
#include "shadercontroller.h"
#include "environment.h"
#include "uielement.h"
#include "escbox.h"
#include "inputmanager.h"
#include "scenec.h"

class scenegame : public scene
{
    public:
        scenegame();
        virtual ~scenegame();

        bool showingescbox {false};
        bool showinginventory {false};

        void shutdownworld();
        void pressedesc();
        void toggleinventory();
        void setkeys();

        void render();
        void show();
        void hide();
        void destroy();

        void update();
        void initialize();

    protected:

    private:
};

#endif // SCENEGAME_H
