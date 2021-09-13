#include "consts.h"
#include "blocktracer.h"

#include "chunk.h"
#include "chunkcontroller.h"
#include "tiledata.h"
#include "chunkcoords.h"

namespace blocktracer
{

}

blocktracer::hitblock blocktracer::traceblocks(wposition startposition, direction tracedirection, float maxdistance)
{
    //https://gamedev.stackexchange.com/questions/47362/cast-ray-to-select-block-in-voxel-game
    //https://gamedev.stackexchange.com/questions/87075/c-ray-traversing-in-3d-voxel-game

    chunkpos curcpos = chunkcoords::wpostocpos(startposition);
    chunkpos oldcpos = curcpos;
    oldcpos.x += 1;
    chunk* curchunk;

    ctilepos curwtpos = chunkcoords::wpostowtilepos(startposition);
    ctilepos oldwtpos = curwtpos;

    wposition curpos = startposition;

    hitblock hit;

    if (tracedirection.x == 0.0f && tracedirection.y == 0.0f && tracedirection.z == 0.0f) return hit;

    direction delta = tracedirection / 10.0f; //lazy test

    float dist = 0.0f;

    bool hittile = false;

    tilesideid hitside = tilesideid::xm;

    while (true)
    {
        if (curwtpos.y < 0) break;
        if (curwtpos.y >= chunkheight) break;

        if (curwtpos != oldwtpos)
        {
            curcpos = chunkcoords::wtilepostocpos(curwtpos);
        }

        if (oldcpos != curcpos)
        {
            if (chunkcontroller::chunkexists(curcpos))
            {
                curchunk = &chunkcontroller::getchunk(curcpos);
                if (!curchunk->allowstilereads())
                {
                    break;
                }
                oldcpos = curcpos;
            }
            else
            {
                break;
            }
        }

        if (curwtpos != oldwtpos)
        {
            glm::ivec3 differando = oldwtpos - curwtpos;

            if (differando.x && differando.y) differando.y = 0;
            if (differando.z && differando.y) differando.z = 0;

            for (int a = 0; a < 6; a++)
            {
                if (sideoffsets[a] == differando) hitside = static_cast<tilesideid>(a);
            }

            oldwtpos = curwtpos;
            if (curchunk->gettile(chunkcoords::wtilepostoctilepos(curwtpos)) > 1)
            {
                hittile = true;
                break;
            }
        }

        if (dist > maxdistance)
        {
            break;
        }

        dist += glm::length(delta);

        curpos += delta;
        curwtpos = chunkcoords::wpostowtilepos(curpos);
    }

    if (hittile)
    {
        hit.cpos = curcpos;
        hit.ctpos = chunkcoords::wpostoctilepos(curwtpos);
        hit.hitside = hitside;
    }

    return hit;

}

