#include "consts.h"
#include "physicsmanager.h"

#include "chunkcontroller.h"
#include "tiledata.h"
#include "timekeeper.h"

namespace physicsmanager
{

}

void physicsmanager::dophysics(physicsobject& p)
{
    if (p.btype == physicsobject::BB_POINT)
        pointphysics(p);
}

void physicsmanager::pointphysics(physicsobject& p)
{
    p.updatevelocity();

    float timefactor = timekeeper::gettimefactor();
    wposition newpos = p.position;
    velocity vel = p.vel * timefactor;
    p.onfloor = false;

    for (int a = 0; a < 3; a++)
    {
        if (vel[a])
        {
            wposition nextpos = p.position;
            nextpos[a] += vel[a];
            tileid tid = chunkcontroller::gettileid(nextpos);
            if (tiledata::ispassable(tid))
            {
                newpos[a] += vel[a];
            }
            else
            {
                if (vel[a] < 0)
                    newpos[a] = floor(newpos[a]) + 0.0001f;
                else
                    newpos[a] = ceil(newpos[a]) - 0.0001f;
                vel[a] = 0;

                if (a == 1)
                {
                    p.onfloor = true;
                }
            }
        }
    }

    if (p.onfloor)
    {
        vel[0] /= 4.0f;
        vel[2] /= 4.0f;

        if (abs(vel[0]) < 0.02f) vel[0] = 0.0f;
        if (abs(vel[2]) < 0.02f) vel[2] = 0.0f;
    }

    p.position = newpos;
    p.vel = vel / timefactor;
}

void physicsmanager::boxphysics(physicsobject& p)
{
    //std::cout << "coolio ";

    p.updatevelocity();
    wposition newpos = p.position;
    float timefactor = timekeeper::gettimefactor();
    velocity vel = p.vel * timefactor; //kan kræsje hvis vel > 1.0
    p.onfloor = false;

    point bb = p.bbox;

    wposition points[6];
    int8_t pts = 6;

    //std::cout << "a" << timefactor << "-" << p.vel.z << " vs " << vel.z << "\n";

    for (int a = 0; a < 3; a++)
    {
        //std::cout << a;
        if (vel[a])
        {
            //messy - fix (funker bare for mchar bbox)
            if (vel[a] < 0.0f) //negativ
            {
                if (a == 0) //x
                {
                    points[0] = wposition{0.0f, 0.0f, 0.0f};
                    points[1] = wposition{0.0f, 0.0f, bb.z};
                    points[2] = wposition{0.0f, bb.y / 2.0f, 0.0f};
                    points[3] = wposition{0.0f, bb.y / 2.0f, bb.z};
                    points[4] = wposition{0.0f, bb.y, 0.0f};
                    points[5] = wposition{0.0f, bb.y, bb.z};
                    pts = 6;
                }
                if (a == 1) //y
                {
                    points[0] = wposition{0.0f, 0.0f, 0.0f};
                    points[1] = wposition{0.0f, 0.0f, bb.z};
                    points[2] = wposition{bb.x, 0.0f, 0.0f};
                    points[3] = wposition{bb.x, 0.0f, bb.z};
                    pts = 4;
                }
                if (a == 2) //z
                {
                    points[0] = wposition{0.0f, 0.0f, 0.0f};
                    points[1] = wposition{bb.x, 0.0f, 0.0f};
                    points[2] = wposition{0.0f, bb.y / 2.0f, 0.0f};
                    points[3] = wposition{bb.x, bb.y / 2.0f, 0.0f};
                    points[4] = wposition{0.0f, bb.y, 0.0f};
                    points[5] = wposition{bb.x, bb.y, 0.0f};
                    pts = 6;
                }
            }
            if (vel[a] >= 0.0f) //positiv
            {
                if (a == 0) //x
                {
                    points[0] = wposition{bb.x, 0.0f, 0.0f};
                    points[1] = wposition{bb.x, 0.0f, bb.z};
                    points[2] = wposition{bb.x, bb.y / 2.0f, 0.0f};
                    points[3] = wposition{bb.x, bb.y / 2.0f, bb.z};
                    points[4] = wposition{bb.x, bb.y, 0.0f};
                    points[5] = wposition{bb.x, bb.y, bb.z};
                    pts = 6;
                }
                if (a == 1) //y
                {
                    points[0] = wposition{0.0f, bb.y, 0.0f};
                    points[1] = wposition{0.0f, bb.y, bb.z};
                    points[2] = wposition{bb.x, bb.y, 0.0f};
                    points[3] = wposition{bb.x, bb.y, bb.z};
                    pts = 4;
                }
                if (a == 2) //z
                {
                    points[0] = wposition{0.0f, 0.0f, bb.z};
                    points[1] = wposition{bb.x, 0.0f, bb.z};
                    points[2] = wposition{0.0f, bb.y / 2.0f, bb.z};
                    points[3] = wposition{bb.x, bb.y / 2.0f, bb.z};
                    points[4] = wposition{0.0f, bb.y, bb.z};
                    points[5] = wposition{bb.x, bb.y, bb.z};
                    pts = 6;
                }
            }
            bool passable = true;
            //std::cout << " m";
            for (int i = 0; i < pts; i++)
            {
                wposition nextpos = newpos + points[i];
                nextpos[a] += vel[a];
                tileid tid = 0;
                if (nextpos.y >= 0 && nextpos.y < chunkheight) tid = chunkcontroller::gettileid(nextpos);
                if (!tiledata::ispassable(tid))
                {
                    passable = false;
                }
            }
            //std::cout << "o";

            if (passable)
            {
                newpos[a] += vel[a];
            }
            else
            {
                if (vel[a] < 0.0f)
                    newpos[a] = floor(newpos[a]) + 0.0001f;
                else if (vel[a] > 0.0f)
                {
                    newpos[a] += bb[a];
                    newpos[a] = ceil(newpos[a]) - 0.0001f;
                    newpos[a] -= bb[a];
                }

                if (a == 1)
                {
                    if (vel.y > 0.8f)
                        p.falldamage = vel.y * 5.0f;

                    p.onfloor = true;
                }

                vel[a] = 0;
            }
            //std::cout << "rt ";
        }
    }

    //std::cout << "b" << timefactor;

    if (p.onfloor)
    {
        vel[0] /= 4.0f;
        vel[2] /= 4.0f;

        if (abs(vel[0]) < 0.02f) vel[0] = 0.0f;
        if (abs(vel[2]) < 0.02f) vel[2] = 0.0f;
    }

    p.vel = vel / timefactor;
    p.position = newpos;

    //std::cout << "finitos\n";
}
