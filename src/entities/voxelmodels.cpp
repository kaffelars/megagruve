#include "consts.h"
#include "voxelmodels.h"
#include "randfunc.h"
#include "map_obj_manager.h"

namespace voxelmodels
{
    std::unordered_map<std::string, uint32_t> modelidtoid;
    std::vector<voxelmodel> models;

    void addvoxelmodel(voxelmodel& v, std::string modelname);
}

void voxelmodels::initialize()
{
    int seed = randfunc::getseed();
    randfunc::setseed(123);

    //tree
    voxelmodel v;
    voxelmodel av;
    voxelmodel bv;
    voxelmodel tallbv;
    voxelmodel spruce;

    tileid leavesid = tiledata::gettileid("t_leaves");
    tileid logid = tiledata::gettileid("t_log");
    tileid blogid = tiledata::gettileid("t_birch_log");

    for (int a = 1; a < 7; a++)
    {
        v.addpoint(ctilepos(3, a, 3), logid);
        av.addpoint(ctilepos(3, a, 3), logid);
        bv.addpoint(ctilepos(3, a, 3), blogid);
        tallbv.addpoint(ctilepos(3, a, 3), blogid);
        spruce.addpoint(ctilepos(3, a, 3), logid);
    }

    for (int a = 7; a < 14; a++)
    {
        tallbv.addpoint(ctilepos(3, a, 3), blogid);
    }

    av.addpoint(ctilepos(3, 7, 3), logid);
    av.addpoint(ctilepos(3, 8, 3), logid);

    spruce.addpoint(ctilepos(3, 7, 3), logid);
    spruce.addpoint(ctilepos(3, 8, 3), logid);
    spruce.addpoint(ctilepos(3, 9, 3), logid);
    spruce.addpoint(ctilepos(3, 10, 3), logid);

    v.centerbottomtile = ctilepos(3,6,3);
    bv.centerbottomtile = ctilepos(3,6,3);
    av.centerbottomtile = ctilepos(3,8,3);
    spruce.centerbottomtile = ctilepos(3,10,3);
    tallbv.centerbottomtile = ctilepos(3,13,3);

    v.addpoint(ctilepos(3, 0, 3), leavesid);
    spruce.addpoint(ctilepos(3, 0, 3), leavesid);
    av.addpoint(ctilepos(3, 0, 3), leavesid);
    bv.addpoint(ctilepos(3, 0, 3), leavesid);
    tallbv.addpoint(ctilepos(3, 0, 3), leavesid);



    for (int y = 0; y < 3; y++)
    {
        for (int z = 0; z < 7; z++)
        {
            for (int x = 0; x < 7; x++)
            {
                float dist = glm::distance(glm::vec3(x, y, z), glm::vec3(3,2,3));
                float bist = glm::distance(glm::vec3(x, y, z), glm::vec3(3,3,3));
                if (!(x == z && x == 3) && dist < 2.5f && randfunc::noise(x+432,y-6453,z+243,0.2f) > -0.6f)
                    v.addpoint(ctilepos(x, y, z), leavesid);
                if (!(x == z && x == 3) && bist < 3.5f && randfunc::noise(x+3432,y-3453,z+4243,0.2f) > -0.3f)
                    av.addpoint(ctilepos(x, y, z), leavesid);
                if (!(x == z && x == 3) && dist < 2.5f && randfunc::noise(x+645,y-123,z+645,0.2f) < 0.6f)
                    bv.addpoint(ctilepos(x, y, z), leavesid);
                if (!(x == z && x == 3) && dist < 2.5f && randfunc::noise(x-1235,y+1992,z-2241,0.2f) < 0.7f)
                    tallbv.addpoint(ctilepos(x, y, z), leavesid);
            }
        }
    }

    for (int y = 1; y < 9; y++)
    {
        for (int z = 0; z < 7; z++)
        {
            for (int x = 0; x < 7; x++)
            {
                float dist = glm::distance(glm::vec2(x, z), glm::vec2(3,3));
                if (!(x == z && x == 3) && dist < ((y%2) == 0 ? (dist + y)/3 : 1.3f))
                    spruce.addpoint(ctilepos(x, y, z), leavesid);
            }
        }
    }


    addvoxelmodel(v, "vox_oak_tree");
    addvoxelmodel(av, "vox_oak_tree2");
    addvoxelmodel(spruce, "vox_spruce_tree");
    addvoxelmodel(bv, "vox_birch_tree");
    addvoxelmodel(tallbv, "vox_tall_birch_tree");



    voxelmodel c;

    tileid cactusid = tiledata::gettileid("t_cactus");
    c.addpoint(ctilepos(0,0,0), cactusid);
    c.addpoint(ctilepos(0,1,0), cactusid);
    c.addpoint(ctilepos(0,2,0), cactusid);
    c.addpoint(ctilepos(0,3,0), cactusid);
    c.addpoint(ctilepos(0,4,0), cactusid);
    c.addpoint(ctilepos(0,5,0), cactusid);

    c.centerbottomtile = ctilepos(0,5,0);

    addvoxelmodel(c, "vox_cactus");


    voxelmodel tt;

    for (int a = 1; a < 17; a++)
    {
        tt.addpoint(ctilepos(5, a, 5), logid);
    }
    tt.addpoint(ctilepos(5, 0, 5), leavesid);

    for (int y = 0; y < 8; y++)
    {
        for (int z = 0; z < 11; z++)
        {
            for (int x = 0; x < 11; x++)
            {
                float dist = glm::distance(glm::vec3(x, y, z), glm::vec3(5,5,5));
                if (!(x == z && x == 5) && dist < 6.5f && utils::randint(0, 10) < 7)
                    tt.addpoint(ctilepos(x, y, z), leavesid);
            }
        }
    }
    tt.centerbottomtile = ctilepos(5,14,5);

    addvoxelmodel(tt, "vox_talltree");


    tileid ssblock = tiledata::gettileid("t_sandstone_block");

    voxelmodel p;

    for (int y = 0; y < 8; y++)
    {
        for (int x = -y-1; x < y+1; x++)
        {
            for (int z = -y-1; z < y+1; z++)
            {
                p.addpoint(ctilepos(x,y,z), ssblock);
            }
        }
    }

    for (int y = 8; y < 16; y++)
    {
        for (int x = -8; x <= 8; x++)
        {
            for (int z = -8; z <= 8; z++)
            {
                if (x == -8 || x == 8 || z == -8 || z == 8)
                    p.addpoint(ctilepos(x,y,z), ssblock);
            }
        }
    }
    p.centerbottomtile = ctilepos(-1, 7, -1);

    addvoxelmodel(p, "vox_pyramid");

    //hut
    voxelmodel hut;

    tileid brickid = tiledata::gettileid("t_bricks");
    tileid stoneid = tiledata::gettileid("t_stone");
    tileid plankid = tiledata::gettileid("t_planks");
    tileid windowid = tiledata::gettileid("t_window");

    uint32_t odoor = map_obj_manager::getmapobjid("o_door");
    uint32_t ochest = map_obj_manager::getmapobjid("o_chest");

    int hs = 4;

    for (int y = 0; y < 6; y++)
    {
        for (int x = -hs; x <= hs; x++)
        {
            for (int z = -hs; z <= hs; z++)
            {
                if ((x == -hs || x == hs || z == -hs || z == hs) && !(x == -hs && z == 0 && y < 3 && y > 0))
                {
                     if ((z == -2 && y == 1) || (z == 2 && y == 1) || (x == 0 && y == 1)) //windows
                     {
                         hut.addpoint(ctilepos(x,y,z), windowid);
                     }
                     else
                     {
                         hut.addpoint(ctilepos(x,y,z), brickid);
                     }
                }
                else
                {

                    hut.addpoint(ctilepos(x,y,z), 0);
                }

                if (y == 0)
                {
                    if ((z == hs || z == -hs) && (x != -hs && x != hs))
                        hut.addpoint(ctilepos(x,-1,z), brickid); //ceiling
                    else
                        hut.addpoint(ctilepos(x,-1,z), plankid); //ceiling
                }

            }
        }
    }

    //floor
    for (int x = -(hs-1); x <= (hs-1); x++)
    {
        for (int z = -(hs-1); z <= (hs-1); z++)
        {
            hut.addpoint(ctilepos(x,3,z), plankid);
        }
    }

    for (int index = 1; index < 3; index++) //roof
    {
        for (int z = -hs; z <= hs; z++)
        {
            for (int x = -hs+index; x <= hs-index; x++)
            {
                if (index < 2 && (z == -hs || z == hs) && !(x == -hs+index || x == hs-index))
                    hut.addpoint(ctilepos(x,-1-index,z), brickid);
                else
                    hut.addpoint(ctilepos(x,-1-index,z), plankid);
            }
        }
    }

    hut.addmapobject(ctilepos(-hs, 2, 0), odoor, 0, 0);

    hut.centerbottomtile = ctilepos(0, 3, 0);

    addvoxelmodel(hut, "vox_hut");

    //small path
    hut.addpoint(ctilepos(-hs-1, 3, 0), stoneid);
    hut.addpoint(ctilepos(-hs-2, 3, 0), stoneid);

    hut.addpoint(ctilepos(-hs-1, 2, 0), 0);
    hut.addpoint(ctilepos(-hs-2, 2, 0), 0);
    hut.addpoint(ctilepos(-hs-1, 1, 0), 0);
    hut.addpoint(ctilepos(-hs-2, 1, 0), 0);

    addvoxelmodel(hut, "vox_hut_path");



    //small hut
    voxelmodel shut;

    hs = 3;

    for (int y = 0; y < 6; y++)
    {
        for (int x = -hs; x <= hs; x++)
        {
            for (int z = -hs; z <= hs; z++)
            {
                if ((x == -hs || x == hs || z == -hs || z == hs) && !(z == 0 && x == -hs && y < 3 && y > 0))
                {
                     if ((z == -1 && x == hs && y == 1) || (z == 1 && x == hs && y == 1) || (x == 0 && y == 1)) //windows
                     {
                         shut.addpoint(ctilepos(x,y,z), windowid);
                     }
                     else
                     {
                         shut.addpoint(ctilepos(x,y,z), brickid);
                     }
                }
                else
                {

                    shut.addpoint(ctilepos(x,y,z), 0);
                }

                if (y == 0)
                {
                    if ((z == hs || z == -hs) && (x != -hs && x != hs))
                        shut.addpoint(ctilepos(x,-1,z), brickid); //ceiling
                    else
                        shut.addpoint(ctilepos(x,-1,z), plankid); //ceiling
                }

            }
        }
    }

    //floor
    for (int x = -(hs-1); x <= (hs-1); x++)
    {
        for (int z = -(hs-1); z <= (hs-1); z++)
        {
            shut.addpoint(ctilepos(x,3,z), plankid);
        }
    }

    for (int index = 1; index < 2; index++) //roof
    {
        for (int z = -hs; z <= hs; z++)
        {
            for (int x = -hs+index; x <= hs-index; x++)
            {
                /*if (index < 1 && (x == -hs || x == hs) && !(z == -hs+index || z == hs-index))
                    shut.addpoint(ctilepos(x,-1-index,z), brickid);
                else*/
                    shut.addpoint(ctilepos(x,-1-index,z), plankid);
            }
        }
    }

    shut.centerbottomtile = ctilepos(0, 3, 0);

    shut.addmapobject(ctilepos(-hs, 2, 0), odoor, 0, 0);

    addvoxelmodel(shut, "vox_small_hut");

    //small path
    shut.addpoint(ctilepos(-hs-1, 3, 0), stoneid);
    shut.addpoint(ctilepos(-hs-2, 3, 0), stoneid);
    shut.addpoint(ctilepos(-hs-3, 3, 0), stoneid);
    shut.addpoint(ctilepos(-hs-1, 2, 0), 0);
    shut.addpoint(ctilepos(-hs-2, 2, 0), 0);
    shut.addpoint(ctilepos(-hs-3, 2, 0), 0);
    shut.addpoint(ctilepos(-hs-1, 1, 0), 0);
    shut.addpoint(ctilepos(-hs-2, 1, 0), 0);
    shut.addpoint(ctilepos(-hs-3, 1, 0), 0);

    addvoxelmodel(shut, "vox_small_hut_path");

    for (voxelmodel::point& p : hut.points)
    {
        if (p.tid == brickid) p.tid = stoneid;
    }
    for (voxelmodel::point& p : shut.points)
    {
        if (p.tid == brickid) p.tid = stoneid;
    }

    addvoxelmodel(hut, "vox_stone_hut_path");
    addvoxelmodel(shut, "vox_small_stone_hut_path");


    voxelmodel well;

    for (int y = 0; y < 12; y++)
    {
        well.addpoint(ctilepos(-1, y, 0), stoneid);
        well.addpoint(ctilepos(-1, y, 1), stoneid);
        well.addpoint(ctilepos(0, y, 2), stoneid);
        well.addpoint(ctilepos(1, y, 2), stoneid);
        well.addpoint(ctilepos(2, y, 0), stoneid);
        well.addpoint(ctilepos(2, y, 1), stoneid);
        well.addpoint(ctilepos(0, y, -1), stoneid);
        well.addpoint(ctilepos(1, y, -1), stoneid);

        well.addpoint(ctilepos(0, y, 0), 0);
        well.addpoint(ctilepos(1, y, 0), 0);
        well.addpoint(ctilepos(0, y, 1), 0);
        well.addpoint(ctilepos(1, y, 1), 0);
    }

    well.centerbottomtile = ctilepos(0, 1, 0);

    addvoxelmodel(well, "vox_well");

    voxelmodel flowerbed;

    tileid dirtid = tiledata::gettileid("t_dirt");
    tileid flower[3] = {tiledata::gettileid("t_flower1"), tiledata::gettileid("t_flower2"), tiledata::gettileid("t_flower3")};

    for (int x = 0; x < 8; x++)
    {
        for (int z = 0; z < 8; z++)
        {
            if (x == 0 || x == 7 || z == 0 || z == 7)
            {
                flowerbed.addpoint(ctilepos(x,0,z), plankid);
                flowerbed.addpoint(ctilepos(x,-1,z), 0);
            }
            else
            {
                flowerbed.addpoint(ctilepos(x,0,z), dirtid);
                flowerbed.addpoint(ctilepos(x,-1,z), flower[(x+z)%3]);
            }
            flowerbed.addpoint(ctilepos(x,-2,z), 0);
            flowerbed.addpoint(ctilepos(x,-3,z), 0);
        }
    }

    for (int y = 1; y < 6; y++) //pillars
    {
        flowerbed.addpoint(ctilepos(0,y,0), plankid);
        flowerbed.addpoint(ctilepos(7,y,0), plankid);
        flowerbed.addpoint(ctilepos(0,y,7), plankid);
        flowerbed.addpoint(ctilepos(7,y,7), plankid);
    }

    flowerbed.centerbottomtile = ctilepos(3, 0, 3);

    addvoxelmodel(flowerbed, "vox_flowerbed");


    voxelmodel shed;

    hs = 2;

    for (int y = 0; y < 6; y++)
    {
        for (int x = -hs; x <= hs; x++)
        {
            for (int z = -hs; z <= hs; z++)
            {
                if ((x == -hs || x == hs || z == -hs || z == hs) && !(z == 0 && x == -hs && y < 3 && y > 0))
                {
                    if (z == 0 && x == hs && y == 1)
                        shed.addpoint(ctilepos(x,y,z), windowid);
                    else
                    {
                        if (y == 0)
                            shed.addpoint(ctilepos(x,y,z), plankid);
                        else
                            shed.addpoint(ctilepos(x,y,z), stoneid);
                    }

                }
                else
                {
                    if (y == 0 || y == 3)
                    {
                        shed.addpoint(ctilepos(x,y,z), plankid);
                    }
                    else
                    {
                        shed.addpoint(ctilepos(x,y,z), 0);
                    }
                }
            }
        }
    }

    shed.centerbottomtile = ctilepos(0, 3, 0);

    shed.addmapobject(ctilepos(-hs, 2, 0), odoor, 0, 0);
    shed.addmapobject(ctilepos(hs-1, 2, 0), ochest, 0, static_cast<int32_t>(chestloot::village));

    addvoxelmodel(shed, "vox_shed");


    voxelmodel stower;

    hs = 3;

    for (int y = 0; y < 18; y++)
    {
        for (int x = -hs; x <= hs; x++)
        {
            for (int z = -hs; z <= hs; z++)
            {
                if ((x == -hs || x == hs || z == -hs || z == hs) && !(z == 0 && x == -hs && y < 11 && y > 8))
                {
                    if (y == 9 && x == 0)
                        stower.addpoint(ctilepos(x,y,z), windowid);
                    else
                        stower.addpoint(ctilepos(x,y,z), stoneid);
                }
                else
                {
                    if (y == 11 || y == 1)
                        stower.addpoint(ctilepos(x,y,z), plankid);
                    else
                        stower.addpoint(ctilepos(x,y,z), 0);
                }
            }
        }
    }

    stower.addpoint(ctilepos(-hs,-1,-hs), stoneid);
    stower.addpoint(ctilepos(hs,-1,-hs), stoneid);
    stower.addpoint(ctilepos(-hs,-1,hs), stoneid);
    stower.addpoint(ctilepos(hs,-1,hs), stoneid);

    stower.addpoint(ctilepos(-hs,-1,-1), stoneid);
    stower.addpoint(ctilepos(-hs,-1,1), stoneid);
    stower.addpoint(ctilepos(hs,-1,-1), stoneid);
    stower.addpoint(ctilepos(hs,-1,1), stoneid);
    stower.addpoint(ctilepos(-1,-1,hs), stoneid);
    stower.addpoint(ctilepos(1,-1,hs), stoneid);
    stower.addpoint(ctilepos(-1,-1,-hs), stoneid);
    stower.addpoint(ctilepos(1,-1,-hs), stoneid);

    //path
    stower.addpoint(ctilepos(-hs-1,11,0), stoneid);
    stower.addpoint(ctilepos(-hs-2,11,0), stoneid);
    stower.addpoint(ctilepos(-hs-3,11,0), stoneid);

    stower.addpoint(ctilepos(-hs-1,10,0), 0);
    stower.addpoint(ctilepos(-hs-2,10,0), 0);
    stower.addpoint(ctilepos(-hs-3,10,0), 0);
    stower.addpoint(ctilepos(-hs-1,9,0), 0);
    stower.addpoint(ctilepos(-hs-2,9,0), 0);
    stower.addpoint(ctilepos(-hs-3,9,0), 0);

    stower.centerbottomtile = ctilepos(0, 11, 0);
    stower.addmapobject(ctilepos(hs-1, 10, 0), ochest, 0, static_cast<int32_t>(chestloot::blacksmith));

    addvoxelmodel(stower, "vox_small_tower");


    voxelmodel btower;

    hs = 5;

    for (int y = 0; y < 26; y++)
    {
        for (int x = -hs; x <= hs+1; x++)
        {
            for (int z = -hs; z <= hs+1; z++)
            {
                if ((x == -hs || x == hs+1 || z == -hs || z == hs+1))
                {
                    if (y == 9 && x == 0)
                        btower.addpoint(ctilepos(x,y,z), windowid);
                    else
                    {
                        if (y < 18 && y > 15)
                        {
                            if (z == 0 || z == 1 || x == 0 || x == 1)
                                btower.addpoint(ctilepos(x,y,z), 0);
                            else
                                btower.addpoint(ctilepos(x,y,z), stoneid);
                        }
                        else
                        {
                            btower.addpoint(ctilepos(x,y,z), stoneid);
                        }
                    }

                }
                else
                {
                    if (y == 18 || y == 0)
                        btower.addpoint(ctilepos(x,y,z), plankid);
                    else
                        btower.addpoint(ctilepos(x,y,z), 0);
                }
            }
        }
    }

    int bal = 0;

    for (int x = -hs-bal; x <= hs+1+bal; x++)
    {
        for (int z = -hs-bal; z <= hs+1+bal; z++)
        {
            if (x == -hs-bal || x == hs+1+bal || z == -hs-bal || z == hs+1+bal)
            {
                if (bal > 0) btower.addpoint(ctilepos(x,0,z), stoneid);
                btower.addpoint(ctilepos(x,-1,z), stoneid);
                if (((z == -hs-bal || z == hs+1+bal) && x % 2 == 0) || ((x == -hs-bal || x == hs+1+bal) && z % 2 == 0)) btower.addpoint(ctilepos(x,-2,z), stoneid);
                else btower.addpoint(ctilepos(x,-2,z), 0);
            }
            else
            {
                btower.addpoint(ctilepos(x,-1,z), 0);
                btower.addpoint(ctilepos(x,-2,z), 0);
            }
        }
    }

    btower.addpoint(ctilepos(-hs-1,18,0), stoneid);
    btower.addpoint(ctilepos(-hs-1,18,1), stoneid);
    btower.addpoint(ctilepos(hs+2,18,0), stoneid);
    btower.addpoint(ctilepos(hs+2,18,1), stoneid);

    btower.addpoint(ctilepos(0,18,-hs-1), stoneid);
    btower.addpoint(ctilepos(1,18,-hs-1), stoneid);
    btower.addpoint(ctilepos(0,18,hs+2), stoneid);
    btower.addpoint(ctilepos(1,18,hs+2), stoneid);

    btower.centerbottomtile = ctilepos(0, 18, 0);

    addvoxelmodel(btower, "vox_big_tower");

    voxelmodel path;

    path.addpoint(ctilepos(0,0,0), stoneid);
    path.addpoint(ctilepos(1,0,0), stoneid);
    path.addpoint(ctilepos(0,0,1), stoneid);
    path.addpoint(ctilepos(1,0,1), stoneid);

    path.centerbottomtile = ctilepos(0,0,0);

    addvoxelmodel(path, "vox_path");

    voxelmodel wpath;

    wpath.addpoint(ctilepos(0,0,0), plankid);
    wpath.addpoint(ctilepos(1,0,0), plankid);
    wpath.addpoint(ctilepos(0,0,1), plankid);
    wpath.addpoint(ctilepos(1,0,1), plankid);

    wpath.centerbottomtile = ctilepos(0,0,0);

    addvoxelmodel(wpath, "vox_wpath");

    randfunc::setseed(seed);
}

void voxelmodels::addvoxelmodel(voxelmodel& v, std::string modelname)
{
    //centers model
    v.centermodel();

    models.push_back(v);
    uint32_t id = models.size()-1;
    modelidtoid.insert(std::make_pair(modelname, id));
}

voxelmodel& voxelmodels::getvoxelmodel(uint32_t id)
{
    return models[id];
}

uint32_t voxelmodels::getvoxelmodelid(std::string id)
{
    return modelidtoid.at(id);
}

voxelmodel& voxelmodels::getvoxelmodel(std::string id)
{
    uint32_t vid = modelidtoid.at(id);
    return models[vid];
}
