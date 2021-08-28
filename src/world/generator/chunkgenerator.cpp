#include "consts.h"
#include "chunkgenerator.h"
#include "chunkcontroller.h"
#include "chunklight.h"
#include "chunkdecorator.h"

chunkgenerator::chunkgenerator()
{
    //ctor
}

chunkgenerator::~chunkgenerator()
{
    //dtor
}

void chunkgenerator::generator(chunk& c)
{
    //empty
    std::cout << "noe er galt";
}

void chunkgenerator::addtile(chunk& c, ctilepos ctpos, tileid tid)
{
    c.settile(ctpos, tid);
}

void chunkgenerator::generatechunk(chunk& c)
{
    initializechunk(c);

    generator(c);

    chunklight::generatesunlight(c);

    finalizechunk(c);
}

void chunkgenerator::initializechunk(chunk& c)
{
    dimensions dims = c.cdims;
    chunkpos cposoffset = c.cpos;
    cposoffset.x *= chunkwidth;
    cposoffset.y *= chunkwidth;

    //biomes
    for (int32_t a = 0; a < (chunkwidth+1)*(chunkwidth+1); a++) //hvorfor +1??
        c.addbiome();

    for (int a = 0; a < (chunkwidth+2) * (chunkwidth+2) * chunkheight; a++)
        c.addlight();

    for (int a = 0; a < (chunkwidth+2) * (chunkwidth+2) * chunkheight; a++)
        c.addtile(0);
}

void chunkgenerator::finalizechunk(chunk& c)
{
    chunkcontroller::threadcounter --;

    c.settag(chunk::C_GENERATED);
}

