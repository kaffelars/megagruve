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

        /*physicsobject pobject {
            wposition{50.5f, 78.0f, 0.5f},
            velocity{0.0f, 0.0f, 0.0f},
            point{0.8f, 1.8f, 0.8f},
            physicsobject::BB_BOX,
            1.0f
        };*/


        wposition cameraoffset {wposition{0.2f, 0.2f, 0.2f}};
        wposition geteyeposition();

        rotation rot { rotation{855.0f, 0.0f} };

        void usecurrentlyselecteditem(bool useup);
        void additem(inventory::invitem iitem);

        inventory mcharinv {40};

        inventory equipment {5};

        int32_t getitemusecooldown(uint32_t actionbarid);
        void setitemusecooldown(uint32_t actionbarid, uint32_t cooldown);
        void setitemusecooldowndelta(uint32_t actionbarid, uint32_t cooldownchange);

        bool flying;
        bool noclip;
        void toggleflying();
        void togglenoclip();

        void updatecamera();
        void fillinv();

        direction getviewdir();
        hdirection gethviewdir();

        int32_t actionbarselection {0};
        int32_t itemusecooldown[10] = {0,0,0,0,0,0,0,0,0,0};

        void movehoriz(hdirection dir);
        void rotateview(rotation r);
        void moveflying(hdirection movement);

    protected:

    private:

};

#endif // MAINCHAR_H
