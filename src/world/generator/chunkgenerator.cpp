#include "consts.h"
#include "chunkgenerator.h"
#include "chunkcontroller.h"
#include "chunklight.h"
#include "chunkdecorator.h"

#include "randfunc.h"

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

void chunkgenerator::decorate(chunk& c)
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

    sethighest(c);

    decorate(c);

    chunklight::generatelight(c);

    finalizechunk(c);
}

void chunkgenerator::sethighest(chunk& c)
{
    //highest
    for (htile z = 0; z < chunkwidth; z++)
    {
        for (htile x = 0; x < chunkwidth; x++)
        {
            bool hset = false;
            for (ytile y = 0; y < chunkheight; y++)
            {
                ctilepos tpos = ctilepos(x,y,z);
                tileid tid = c.gettile(tpos);

                if (tid != 0)
                {
                    c.addhighest(y);
                    hset = true;
                    break;
                }
            }

            if (!hset)
                c.addhighest(255);
        }
    }
}

void chunkgenerator::initializechunk(chunk& c)
{
    //dimensions dims = c.cdims;
    chunkpos cposoffset = c.cpos;
    cposoffset.x *= chunkwidth;
    cposoffset.y *= chunkwidth;

    //biomes
    for (int32_t a = 0; a < (chunkwidth+2)*(chunkwidth+2); a++) //hvorfor +1??
        c.addbiome();

    for (int a = 0; a < (chunkwidth+2) * (chunkwidth+2) * chunkheight; a++)
        c.addtile(0);
}

void chunkgenerator::finalizechunk(chunk& c)
{
    chunkcontroller::threadcounter --;

    c.settag(chunk::C_GENERATED);
}

