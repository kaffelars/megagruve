#include "consts.h"
#include "voxelmodels.h"

namespace voxelmodels
{
    std::unordered_map<std::string, uint32_t> modelidtoid;
    std::vector<voxelmodel> models;
}

void voxelmodels::initialize()
{
    //tree
    voxelmodel v;
    voxelmodel bv;

    tileid leavesid = tiledata::gettileid("t_leaves");
    tileid logid = tiledata::gettileid("t_log");
    tileid blogid = tiledata::gettileid("t_birch_log");

    for (int a = 1; a < 7; a++)
    {
        v.addpoint(ctilepos(3, a, 3), logid);
        bv.addpoint(ctilepos(3, a, 3), blogid);
    }


    v.centerbottomtile = ctilepos(3,6,3);
    bv.centerbottomtile = ctilepos(3,6,3);

    v.addpoint(ctilepos(3, 0, 3), leavesid);
    bv.addpoint(ctilepos(3, 0, 3), leavesid);

    for (int y = 0; y < 3; y++)
    {
        for (int z = 0; z < 7; z++)
        {
            for (int x = 0; x < 7; x++)
            {
                float dist = glm::distance(glm::vec3(x, y, z), glm::vec3(3,2,3));
                if (!(x == z && x == 3) && dist < 2.5f && utils::randint(0, 10) < 8)
                    v.addpoint(ctilepos(x, y, z), leavesid);
                if (!(x == z && x == 3) && dist < 2.5f && utils::randint(0, 10) > 2)
                    bv.addpoint(ctilepos(x, y, z), leavesid);
            }
        }
    }


    models.push_back(v);
    uint32_t id = models.size()-1;
    modelidtoid.insert(std::make_pair("vox_tree", id));

    models.push_back(bv);
    id = models.size()-1;
    modelidtoid.insert(std::make_pair("vox_birch_tree", id));


    voxelmodel c;

    tileid cactusid = tiledata::gettileid("t_cactus");
    c.addpoint(ctilepos(0,0,0), cactusid);
    c.addpoint(ctilepos(0,1,0), cactusid);
    c.addpoint(ctilepos(0,2,0), cactusid);
    c.addpoint(ctilepos(0,3,0), cactusid);
    c.addpoint(ctilepos(0,4,0), cactusid);
    c.addpoint(ctilepos(0,5,0), cactusid);

    c.centerbottomtile = ctilepos(0,5,0);

    models.push_back(c);
    id = models.size()-1;
    modelidtoid.insert(std::make_pair("vox_cactus", id));


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

    models.push_back(tt);
    id = models.size()-1;
    modelidtoid.insert(std::make_pair("vox_talltree", id));
}

voxelmodel& voxelmodels::getvoxelmodel(uint32_t id)
{
    return models[id];
}

voxelmodel& voxelmodels::getvoxelmodel(std::string id)
{
    uint32_t vid = modelidtoid.at(id);
    return models[vid];
}
