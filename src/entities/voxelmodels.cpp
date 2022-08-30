#include "consts.h"
#include "voxelmodels.h"
#include "randfunc.h"

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
