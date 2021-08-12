#ifndef ENTITY_H
#define ENTITY_H



class entity
{
	public:
        virtual ~entity() = default;
        virtual void heal(uint32_t healamount);
        virtual void takedamage(int32_t attackstrength, int32_t attacktype, entity* source);
        virtual void applybuff(std::string buffname);
        virtual wposition getposition();
        virtual int32_t getid();
};


class blockentity : public entity
{
	blockentity(wtilepos tilepos);

	wtilepos wtpos;
	int health;

    void resethealth();
	wposition getposition ();
	void takedamage (int32_t attackstrength, int32_t attacktype, entity* source);
	void destroytile ();
	int32_t getid();
};

/*class itementity :: public entity
{
	//for invitems
};*/



#endif // ENTITY_H
