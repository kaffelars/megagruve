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

void chunkwatermanager::clearactivewatertiles()
{
    activewatertiles.clear();
}

void chunkwatermanager::updateactivewatertiles()
{
    //std::cout << "\nactive water tiles: " << activewatertiles.size() << "\n";
    std::vector<activewatertile> redotiles;
    int tid_waterflow = tiledata::gettileid("t_waterflow1");
    int tid_water = tiledata::gettileid("t_water");

    for (activewatertile& a : activewatertiles)
    {
        chunk& c = chunkcontroller::getchunk(a.cpos);
        if (c.gettag() == chunk::C_READY)// || c.gettag() == chunk::C_REMESHED)
        {
            //if (chunkcoords::withinchunkbounds(a.ctpos))
            //{
                int waterlevel = c.gettile(a.ctpos);
                int newwaterlevel;
                if (waterlevel == tid_water) newwaterlevel = tid_waterflow;
                else newwaterlevel = waterlevel + 1;
                if (newwaterlevel > tid_waterflow + 5) newwaterlevel = 0;

                bool downflow = false;

                if (chunkcoords::withinextendedchunkbounds(a.ctpos + sideoffsets[3]))
                {
                    tileid tid = c.gettile(a.ctpos + sideoffsets[3]);
                    if (tiledata::isempty(tid) || tiledata::iswater(tid))
                    {
                        chunktilemanager::breakageinfo b;
                        chunktilemanager::addctiletochange(a.cpos, a.ctpos + sideoffsets[3], tid_water, 0, b);
                        downflow = true;
                    }
                }

                if (!downflow)
                {
                    for (int i = 0; i < 6; i++)
                    {
                        if (i != 2 && i != 3)
                        {
                            if (chunkcoords::withinextendedchunkbounds(a.ctpos + sideoffsets[i]))
                            {
                                tileid tid = c.gettile(a.ctpos + sideoffsets[i]);
                                if (tiledata::isempty(tid) && newwaterlevel != 0)
                                {
                                    chunktilemanager::breakageinfo b;
                                    chunktilemanager::addctiletochange(a.cpos, a.ctpos + sideoffsets[i], newwaterlevel, 0, b);
                                }
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
