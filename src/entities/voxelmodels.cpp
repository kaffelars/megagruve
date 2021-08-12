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

    tileid leavesid = tiledata::gettileid("t_leaves");
    tileid logid = tiledata::gettileid("t_log");

    v.addpoint(ctilepos(3, 1, 3), logid);
    v.addpoint(ctilepos(3, 2, 3), logid);
    v.addpoint(ctilepos(3, 3, 3), logid);
    v.addpoint(ctilepos(3, 4, 3), logid);
    v.addpoint(ctilepos(3, 5, 3), logid);
    v.addpoint(ctilepos(3, 6, 3), logid);

    v.centerbottomtile = ctilepos(3,6,3);

    v.addpoint(ctilepos(3, 0, 3), leavesid);
    v.addpoint(ctilepos(2, 0, 3), leavesid);
    v.addpoint(ctilepos(3, 0, 2), leavesid);
    v.addpoint(ctilepos(4, 0, 3), leavesid);
    v.addpoint(ctilepos(3, 0, 4), leavesid);

    v.addpoint(ctilepos(2, 1, 1), leavesid);
    v.addpoint(ctilepos(3, 1, 1), leavesid);
    v.addpoint(ctilepos(4, 1, 1), leavesid);

    v.addpoint(ctilepos(1, 1, 2), leavesid);
    v.addpoint(ctilepos(2, 1, 2), leavesid);
    v.addpoint(ctilepos(3, 1, 2), leavesid);
    v.addpoint(ctilepos(4, 1, 2), leavesid);
    v.addpoint(ctilepos(5, 1, 2), leavesid);

    v.addpoint(ctilepos(1, 1, 3), leavesid);
    v.addpoint(ctilepos(2, 1, 3), leavesid);
    v.addpoint(ctilepos(4, 1, 3), leavesid);
    v.addpoint(ctilepos(5, 1, 3), leavesid);

    v.addpoint(ctilepos(1, 1, 4), leavesid);
    v.addpoint(ctilepos(2, 1, 4), leavesid);
    v.addpoint(ctilepos(3, 1, 4), leavesid);
    v.addpoint(ctilepos(4, 1, 4), leavesid);
    v.addpoint(ctilepos(5, 1, 4), leavesid);

    v.addpoint(ctilepos(2, 1, 5), leavesid);
    v.addpoint(ctilepos(3, 1, 5), leavesid);
    v.addpoint(ctilepos(4, 1, 5), leavesid);

    v.addpoint(ctilepos(1, 2, 1), leavesid);
    v.addpoint(ctilepos(2, 2, 1), leavesid);
    v.addpoint(ctilepos(3, 2, 1), leavesid);
    v.addpoint(ctilepos(4, 2, 1), leavesid);
    v.addpoint(ctilepos(5, 2, 1), leavesid);

    v.addpoint(ctilepos(1, 2, 2), leavesid);
    v.addpoint(ctilepos(2, 2, 2), leavesid);
    v.addpoint(ctilepos(3, 2, 2), leavesid);
    v.addpoint(ctilepos(4, 2, 2), leavesid);
    v.addpoint(ctilepos(5, 2, 2), leavesid);

    v.addpoint(ctilepos(1, 2, 3), leavesid);
    v.addpoint(ctilepos(2, 2, 3), leavesid);
    v.addpoint(ctilepos(4, 2, 3), leavesid);
    v.addpoint(ctilepos(5, 2, 3), leavesid);

    v.addpoint(ctilepos(1, 2, 4), leavesid);
    v.addpoint(ctilepos(2, 2, 4), leavesid);
    v.addpoint(ctilepos(3, 2, 4), leavesid);
    v.addpoint(ctilepos(4, 2, 4), leavesid);
    v.addpoint(ctilepos(5, 2, 4), leavesid);

    v.addpoint(ctilepos(1, 2, 5), leavesid);
    v.addpoint(ctilepos(2, 2, 5), leavesid);
    v.addpoint(ctilepos(3, 2, 5), leavesid);
    v.addpoint(ctilepos(4, 2, 5), leavesid);
    v.addpoint(ctilepos(5, 2, 5), leavesid);


    v.addpoint(ctilepos(2, 2, 0), leavesid);
    v.addpoint(ctilepos(3, 2, 0), leavesid);
    v.addpoint(ctilepos(4, 2, 0), leavesid);

    v.addpoint(ctilepos(2, 2, 6), leavesid);
    v.addpoint(ctilepos(3, 2, 6), leavesid);
    v.addpoint(ctilepos(4, 2, 6), leavesid);

    v.addpoint(ctilepos(0, 2, 2), leavesid);
    v.addpoint(ctilepos(0, 2, 3), leavesid);
    v.addpoint(ctilepos(0, 2, 4), leavesid);

    v.addpoint(ctilepos(6, 2, 2), leavesid);
    v.addpoint(ctilepos(6, 2, 3), leavesid);
    v.addpoint(ctilepos(6, 2, 4), leavesid);


    models.push_back(v);
    uint32_t id = models.size()-1;
    modelidtoid.insert(std::make_pair("vox_tree", id));

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
}

voxelmodel& voxelmodels::getvoxelmodel(std::string id)
{
    uint32_t vid = modelidtoid.at(id);
    return models[vid];
}
