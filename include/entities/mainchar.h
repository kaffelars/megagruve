#ifndef MAINCHAR_H
#define MAINCHAR_H

#include "physicsobject.h"
#include "boundingbox.h"
#include "camera.h"
#include "utils.h"
#include "timekeeper.h"
#include "inventory.h"
#include "lifeform.h"

class mainchar : public lifeform
{
    public:
        mainchar();
        virtual ~mainchar();

        //entityvitals evitals {20, 0};

        physicsobject pobject {
            wposition{50.5f, 78.0f, 0.5f},
            velocity{0.0f, 0.0f, 0.0f},
            point{0.8f, 1.8f, 0.8f},
            physicsobject::BB_BOX,
            1.0f
        };

        wposition getposition();
        wposition cameraoffset {wposition{0.4f, 0.2f, 0.4f}};
        wposition geteyeposition();

        rotation rot { rotation{855.0f, 0.0f} };

        inventory mcharinv {40};

        void updatecamera();
        void fillinv();

        direction getviewdir();
        hdirection gethviewdir();
        void addvelocity(direction vel);
        void movehoriz(hdirection dir);
        void rotateview(rotation r);
        void moveflying(hdirection movement);

    protected:

    private:

};

#endif // MAINCHAR_H
