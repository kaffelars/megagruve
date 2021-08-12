#include "consts.h"
#include "statnumbers.h"


statnumbers::statnumbers()
{
    //ctor
}

statnumbers::~statnumbers()
{
    //dtor
}


statnumbers operator+(const statnumbers& a, const statnumbers& b)
{
    statnumbers s;
    s.maxhp = a.maxhp + b.maxhp;
    s.attack = a.attack + b.attack;
    s.defense = a.defense + b.defense;
    s.movespeed = a.movespeed + b.movespeed;
    s.usespeed = a.usespeed + b.usespeed;
	return s;
}
