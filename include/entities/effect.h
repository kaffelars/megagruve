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

class applybuff : public effect
{
	public:
		applybuff(std::string bname);
		virtual ~applybuff() = default;
        bool activate(entity* user, entity* target);

	private:
		std::string buffname;

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

class changeblockeffect:public effect
{
	public:
        changeblockeffect(bool onlyemptyblocks, tileid block);
        virtual ~changeblockeffect() = default;
        bool activate(entity* user, entity* target);
    private:
        uint32_t tid;
        bool emptyonly;
};



#endif // EFFECT_H
