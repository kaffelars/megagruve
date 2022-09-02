#ifndef EFFECT_H
#define EFFECT_H


#include "entity.h"

class effect
{
    public:
        effect() = default;
        virtual ~effect() = default;
        virtual bool activate(entity* user, entity* target) = 0;
};

class healeffect : public effect
{
	public:
		healeffect(int32_t healstr);
		virtual ~healeffect() = default;
		bool activate(entity* user, entity* target);

	private:
		int32_t healstrength;
};

class togglelight : public effect
{
	public:
		togglelight(float lightstr);
		virtual ~togglelight() = default;
		bool activate(entity* user, entity* target);

	private:
		float lightstrength;
};

class movetime : public effect
{
	public:
		movetime(float timetomove);
		virtual ~movetime() = default;
		bool activate(entity* user, entity* target);

	private:
		float timemovement;
};

class applybuff : public effect
{
	public:
		applybuff(std::string bname);
		virtual ~applybuff() = default;
        bool activate(entity* user, entity* target);

	private:
		std::string buffname;

};

class shootparticle:public effect
{
    public:
        shootparticle(uint32_t particlenum, uint8_t particletex, int32_t particlespread);
        virtual ~shootparticle() = default;
        bool activate(entity* user, entity* target);
    private:
        uint32_t num;
        uint8_t texid;
        int32_t spread;
};

class toggleflying:public effect
{
    public:
        toggleflying();
        virtual ~toggleflying() = default;
        bool activate(entity* user, entity* target);
    private:
};

class explodeblocks:public effect
{
    public:
        explodeblocks(uint32_t explosionpower);
        virtual ~explodeblocks() = default;
        bool activate(entity* user, entity* target);
    private:
        uint32_t power;
};

class throwexplosive:public effect
{
    public:
        throwexplosive(uint32_t explosionpower, uint32_t textureid, uint32_t spritesize);
        virtual ~throwexplosive() = default;
        bool activate(entity* user, entity* target);
    private:
        uint32_t power;
        uint32_t texid;
        uint32_t ssize;
};

class attackeffect:public effect
{
	public:
		attackeffect(int32_t attackstr, int32_t atype);
        virtual ~attackeffect() = default;
		bool activate(entity* user, entity* target);
	private:
        int32_t attackstrength;
        int32_t attacktype;
};

class changeweathereffect:public effect
{
	public:
        changeweathereffect(float weatherchange);
        virtual ~changeweathereffect() = default;
        bool activate(entity* user, entity* target);
    private:
        float change;
};

class toggletime:public effect
{
	public:
        toggletime();
        virtual ~toggletime() = default;
        bool activate(entity* user, entity* target);
    private:
};

class changeblockeffect:public effect
{
	public:
        changeblockeffect(bool onlyemptyblocks, bool addtheblock, tileid block);
        virtual ~changeblockeffect() = default;
        bool activate(entity* user, entity* target);
    private:
        uint32_t tid;
        bool emptyonly;
        bool addblock;
};

class placeobjecteffect:public effect
{
	public:
        placeobjecteffect(bool onlyemptyblocks, uint32_t objid);
        virtual ~placeobjecteffect() = default;
        bool activate(entity* user, entity* target);
    private:
        uint32_t tid;
        bool emptyonly;
};



#endif // EFFECT_H
