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

void statnumbers::changestat(stat stattochange, float valuetoadd)
{
    statvalues[stattochange] += valuetoadd;
}

void statnumbers::setstat(stat stattoset, float value)
{
    statvalues[stattoset] = value;
}

float statnumbers::getstat(stat stattoget)
{
    return statvalues[stattoget];
}

statnumbers operator+(const statnumbers& a, const statnumbers& b)
{
    statnumbers s;
    for (int i = 0; i < 5; i++)
    {
        s.statvalues[i] = a.statvalues[i] + b.statvalues[i];
    }


	return s;
}
