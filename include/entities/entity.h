#ifndef ENTITY_H
#define ENTITY_H

#include "model.h"

class entity
{
	public:
        virtual ~entity() = default;
        virtual void heal(int32_t healamount);
        virtual void takedamage(int32_t attackstrength, int32_t attacktype, entity* source);
        virtual void applybuff(std::string buffname);
        virtual wposition getposition();
        //virtual void setposition(wposition wpos);
        virtual int32_t getid();
        virtual bool interact(); //for right click
        virtual bool destroy() ;
        virtual model& getmodel();
        virtual void setfacingdirection(tilesideid tsid);
        int32_t getfacingdirectionid();
        tilesideid facingdirection {tilesideid::xm};
        virtual direction getviewdir();

};


class blankentity : public entity
{
    public:
        blankentity() = default;
};


class blockentity : public entity
{
    public:
        blockentity(wtilepos tilepos);

        wtilepos wtpos;
        int32_t health;
        int32_t getcurrenthealth();
        void heal(int32_t healamount);
        void resethealth();
        wposition getposition ();
        void setposition(wtilepos tilepos);
        void takedamage (int32_t attackstrength, int32_t attacktype, entity* source);
        bool destroy ();
        int32_t getid();
};

/*class itementity :: public entity
{
	//for invitems
};*/



#endif // ENTITY_H
