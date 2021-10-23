#include "consts.h"
#include "chunkwatermanager.h"
#include "chunk.h"
#include "chunkcontroller.h"
#include "chunkcoords.h"
#include "tiledata.h"
#include "chunktilemanager.h"

namespace chunkwatermanager
{
    struct activewatertile
    {
        chunkpos cpos;
        ctilepos ctpos;
    };

    std::vector<activewatertile> activewatertiles;
}


void chunkwatermanager::updateactivewatertiles()
{
    //std::cout << "\nactive water tiles: " << activewatertiles.size() << "\n";
    std::vector<activewatertile> redotiles;

    for (activewatertile& a : activewatertiles)
    {
        chunk& c = chunkcontroller::getchunk(a.cpos);
        if (c.gettag() == chunk::C_READY)// || c.gettag() == chunk::C_REMESHED)
        {
            //if (chunkcoords::withinchunkbounds(a.ctpos))
            //{
                for (int i = 0; i < 6; i++)
                {
                    if (i != 2) //vann kan ikke gå oppover
                    {
                        if (chunkcoords::withinextendedchunkbounds(a.ctpos + sideoffsets[i]))
                        {
                            tileid tid = c.gettile(a.ctpos + sideoffsets[i]);
                            if (tiledata::isempty(tid))
                            {
                                chunktilemanager::breakageinfo b;
                                chunktilemanager::addctiletochange(a.cpos, a.ctpos + sideoffsets[i], 1, 0, b);
                            }
                        }
                    }
                }
            //}
        }
        else
        {
            redotiles.push_back(a);
        }
    }

    activewatertiles.clear();

    activewatertiles = redotiles;
}

void chunkwatermanager::addactivewatertile(chunkpos cpos, ctilepos ctpos)
{
    activewatertiles.push_back(activewatertile{cpos, ctpos});
}
