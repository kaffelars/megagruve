#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "boundingbox.h"

class physicsobject
{
    public:
        physicsobject(wposition p, velocity v, boundingbox::box b);// std::vector<boundingbox::box>& fbbox);
        physicsobject();

        virtual ~physicsobject();

        wposition getposition();
        wposition getnextposition();

        boundingbox bbox;

        void addvelocity(velocity v);
        void stop();
        void setposition(wposition p);
        void addposition(wposition p);
        void setvelocity(velocity v);

        void updatevelocity();

        void updateposition();
    protected:

    private:
        wposition position {wposition{0.0f, 0.0f, 0.0f}};
        velocity vel {velocity{0.0f, 0.0f, 0.0f}};
};

#endif // PHYSICSOBJECT_H
