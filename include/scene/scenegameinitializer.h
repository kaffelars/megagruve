#ifndef SCENEGAMEINITIALIZER_H
#define SCENEGAMEINITIALIZER_H

#include "scene.h"

class scenegameinitializer : public scene
{
    public:
        scenegameinitializer();
        virtual ~scenegameinitializer();

        void render();
        void show();
        void hide();
        void destroy();

        void update();
        void hiddenupdate();
        void initialize();
        void changewindowsize();

        int currentstep;

        void beginnewworld();

    protected:

    private:
};

#endif // SCENEGAMEINITIALIZER_H
