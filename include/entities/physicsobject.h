#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "boundingbox.h"

class physicsobject
{
    public:
        enum bbtype
        {
            BB_POINT, BB_LINE, BB_BOX
        };

        physicsobject(wposition p, velocity v, point b, bbtype btyp, float gfactor);// std::vector<boundingbox::box>& fbbox);
        physicsobject();

        virtual ~physicsobject();

        virtual wposition getposition();
        wposition getnextposition();

        int32_t falldamage;

        void dophysics();

        bool resting;
        bool onfloor;

        bbtype btype;

        point bbox;

        float gravityfactor;

        void addvelocity(velocity v);
        void stop();
        void setposition(wposition p);
        void addposition(wposition p);
        void setvelocity(velocity v);

        void updatevelocity();

        void updateposition();

        wposition position {wposition{0.0f, 0.0f, 0.0f}};
        velocity vel {velocity{0.0f, 0.0f, 0.0f}};
    protected:

    private:

};

#endif // PHYSICSOBJECT_H
