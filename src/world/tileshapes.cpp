#include "consts.h"
#include "tiledata.h"

namespace tiledata
{
    std::vector<tileshape> tileshapes;
    uint8_t tilesidevalues[6] = {1, 2, 4, 8, 16, 32};
    vnorm sidenormals[6] = {vnorm{-1,0,0}, vnorm{1,0,0}, vnorm{0,-1,0}, vnorm{0,1,0}, vnorm{0,0,-1}, vnorm{0,0,1}};
}

void tiledata::initializetileshapes()
{
    tileshape t;

    t.vertexes[0].push_back(vpos{0, 0, 0});
    t.vertexes[0].push_back(vpos{0, 0, 1});
    t.vertexes[0].push_back(vpos{0, 1, 0});
    t.vertexes[0].push_back(vpos{0, 0, 1});
    t.vertexes[0].push_back(vpos{0, 1, 1});
    t.vertexes[0].push_back(vpos{0, 1, 0});

    t.vertexes[1].push_back(vpos{1, 0, 0});
    t.vertexes[1].push_back(vpos{1, 1, 0});
    t.vertexes[1].push_back(vpos{1, 0, 1});
    t.vertexes[1].push_back(vpos{1, 1, 1});
    t.vertexes[1].push_back(vpos{1, 0, 1});
    t.vertexes[1].push_back(vpos{1, 1, 0});

    t.vertexes[2].push_back(vpos{0, 0, 0});
    t.vertexes[2].push_back(vpos{1, 0, 0});
    t.vertexes[2].push_back(vpos{1, 0, 1});
    t.vertexes[2].push_back(vpos{0, 0, 0});
    t.vertexes[2].push_back(vpos{1, 0, 1});
    t.vertexes[2].push_back(vpos{0, 0, 1});

    t.vertexes[3].push_back(vpos{1, 1, 0});
    t.vertexes[3].push_back(vpos{0, 1, 0});
    t.vertexes[3].push_back(vpos{1, 1, 1});
    t.vertexes[3].push_back(vpos{1, 1, 1});
    t.vertexes[3].push_back(vpos{0, 1, 0});
    t.vertexes[3].push_back(vpos{0, 1, 1});

    t.vertexes[4].push_back(vpos{0, 0, 0});
    t.vertexes[4].push_back(vpos{0, 1, 0});
    t.vertexes[4].push_back(vpos{1, 1, 0});
    t.vertexes[4].push_back(vpos{0, 0, 0});
    t.vertexes[4].push_back(vpos{1, 1, 0});
    t.vertexes[4].push_back(vpos{1, 0, 0});

    t.vertexes[5].push_back(vpos{0, 1, 1});
    t.vertexes[5].push_back(vpos{0, 0, 1});
    t.vertexes[5].push_back(vpos{1, 1, 1});
    t.vertexes[5].push_back(vpos{1, 1, 1});
    t.vertexes[5].push_back(vpos{0, 0, 1});
    t.vertexes[5].push_back(vpos{1, 0, 1});

    t.uv[0].push_back(uvpos{1, 0});
    t.uv[0].push_back(uvpos{0, 0});
    t.uv[0].push_back(uvpos{1, 1});
    t.uv[0].push_back(uvpos{0, 0});
    t.uv[0].push_back(uvpos{0, 1});
    t.uv[0].push_back(uvpos{1, 1});

    t.uv[1].push_back(uvpos{0, 0});
    t.uv[1].push_back(uvpos{0, 1});
    t.uv[1].push_back(uvpos{1, 0});
    t.uv[1].push_back(uvpos{1, 1});
    t.uv[1].push_back(uvpos{1, 0});
    t.uv[1].push_back(uvpos{0, 1});

    t.uv[2].push_back(uvpos{0, 0});
    t.uv[2].push_back(uvpos{1, 0});
    t.uv[2].push_back(uvpos{1, 1});
    t.uv[2].push_back(uvpos{0, 0});
    t.uv[2].push_back(uvpos{1, 1});
    t.uv[2].push_back(uvpos{0, 1});

    t.uv[3].push_back(uvpos{1, 0});
    t.uv[3].push_back(uvpos{0, 0});
    t.uv[3].push_back(uvpos{1, 1});
    t.uv[3].push_back(uvpos{1, 1});
    t.uv[3].push_back(uvpos{0, 0});
    t.uv[3].push_back(uvpos{0, 1});

    t.uv[4].push_back(uvpos{0, 0});
    t.uv[4].push_back(uvpos{0, 1});
    t.uv[4].push_back(uvpos{1, 1});
    t.uv[4].push_back(uvpos{0, 0});
    t.uv[4].push_back(uvpos{1, 1});
    t.uv[4].push_back(uvpos{1, 0});

    t.uv[5].push_back(uvpos{1, 1});
    t.uv[5].push_back(uvpos{1, 0});
    t.uv[5].push_back(uvpos{0, 1});
    t.uv[5].push_back(uvpos{0, 1});
    t.uv[5].push_back(uvpos{1, 0});
    t.uv[5].push_back(uvpos{0, 0});

    tileshapes.push_back(t);

    tileshape x;

    x.vertexes[6].push_back(vpos{0.1465f, 0, 0.1465f});
    x.vertexes[6].push_back(vpos{0.8535f, 0, 0.8535f});
    x.vertexes[6].push_back(vpos{0.1465f, 1, 0.1465f});
    x.vertexes[6].push_back(vpos{0.8535f, 0, 0.8535f});
    x.vertexes[6].push_back(vpos{0.8535f, 1, 0.8535f});
    x.vertexes[6].push_back(vpos{0.1465f, 1, 0.1465f});

    x.vertexes[6].push_back(vpos{0.8535f, 0, 0.8535f});
    x.vertexes[6].push_back(vpos{0.1465f, 0, 0.1465f});
    x.vertexes[6].push_back(vpos{0.1465f, 1, 0.1465f});
    x.vertexes[6].push_back(vpos{0.8535f, 1, 0.8535f});
    x.vertexes[6].push_back(vpos{0.8535f, 0, 0.8535f});
    x.vertexes[6].push_back(vpos{0.1465f, 1, 0.1465f});

    x.vertexes[6].push_back(vpos{0.1465f, 0, 0.8535f});
    x.vertexes[6].push_back(vpos{0.8535f, 0, 0.1465f});
    x.vertexes[6].push_back(vpos{0.1465f, 1, 0.8535f});
    x.vertexes[6].push_back(vpos{0.8535f, 0, 0.1465f});
    x.vertexes[6].push_back(vpos{0.8535f, 1, 0.1465f});
    x.vertexes[6].push_back(vpos{0.1465f, 1, 0.8535f});

    x.vertexes[6].push_back(vpos{0.8535f, 0, 0.1465f});
    x.vertexes[6].push_back(vpos{0.1465f, 0, 0.8535f});
    x.vertexes[6].push_back(vpos{0.1465f, 1, 0.8535f});
    x.vertexes[6].push_back(vpos{0.8535f, 1, 0.1465f});
    x.vertexes[6].push_back(vpos{0.8535f, 0, 0.1465f});
    x.vertexes[6].push_back(vpos{0.1465f, 1, 0.8535f});

    for (int a=0; a < 6; a++)
        x.normals.push_back(vnorm{-0.707f, 0.0f, 0.707f});

    for (int a=0; a < 6; a++)
        x.normals.push_back(vnorm{0.707f, 0.0f, -0.707f});

    for (int a=0; a < 6; a++)
        x.normals.push_back(vnorm{0.707f, 0.0f, 0.707f});

    for (int a=0; a < 6; a++)
        x.normals.push_back(vnorm{-0.707f, 0.0f, -0.707f});

    for (int a = 0; a < 2; a++)
    {
        x.uv[6].push_back(uvpos{1, 0});
        x.uv[6].push_back(uvpos{0, 0});
        x.uv[6].push_back(uvpos{1, 1});
        x.uv[6].push_back(uvpos{0, 0});
        x.uv[6].push_back(uvpos{0, 1});
        x.uv[6].push_back(uvpos{1, 1});

        x.uv[6].push_back(uvpos{0, 0});
        x.uv[6].push_back(uvpos{1, 0});
        x.uv[6].push_back(uvpos{1, 1});
        x.uv[6].push_back(uvpos{0, 1});
        x.uv[6].push_back(uvpos{0, 0});
        x.uv[6].push_back(uvpos{1, 1});
    }


    x.onlyanyways = true;
    x.hasanyways = true;

    tileshapes.push_back(x);

    tileshape cactus;

    cactus.vertexes[6].push_back(vpos{0.0625f, 0, 0});
    cactus.vertexes[6].push_back(vpos{0.0625f, 0, 1});
    cactus.vertexes[6].push_back(vpos{0.0625f, 1, 0});
    cactus.vertexes[6].push_back(vpos{0.0625f, 0, 1});
    cactus.vertexes[6].push_back(vpos{0.0625f, 1, 1});
    cactus.vertexes[6].push_back(vpos{0.0625f, 1, 0});

    cactus.vertexes[6].push_back(vpos{0.9375f, 0, 0});
    cactus.vertexes[6].push_back(vpos{0.9375f, 1, 0});
    cactus.vertexes[6].push_back(vpos{0.9375f, 0, 1});
    cactus.vertexes[6].push_back(vpos{0.9375f, 1, 1});
    cactus.vertexes[6].push_back(vpos{0.9375f, 0, 1});
    cactus.vertexes[6].push_back(vpos{0.9375f, 1, 0});

    cactus.vertexes[2].push_back(vpos{0, 0, 0});
    cactus.vertexes[2].push_back(vpos{1, 0, 0});
    cactus.vertexes[2].push_back(vpos{1, 0, 1});
    cactus.vertexes[2].push_back(vpos{0, 0, 0});
    cactus.vertexes[2].push_back(vpos{1, 0, 1});
    cactus.vertexes[2].push_back(vpos{0, 0, 1});

    cactus.vertexes[3].push_back(vpos{1, 1, 0});
    cactus.vertexes[3].push_back(vpos{0, 1, 0});
    cactus.vertexes[3].push_back(vpos{1, 1, 1});
    cactus.vertexes[3].push_back(vpos{1, 1, 1});
    cactus.vertexes[3].push_back(vpos{0, 1, 0});
    cactus.vertexes[3].push_back(vpos{0, 1, 1});

    cactus.vertexes[6].push_back(vpos{0, 0, 0.0625f});
    cactus.vertexes[6].push_back(vpos{0, 1, 0.0625f});
    cactus.vertexes[6].push_back(vpos{1, 1, 0.0625f});
    cactus.vertexes[6].push_back(vpos{0, 0, 0.0625f});
    cactus.vertexes[6].push_back(vpos{1, 1, 0.0625f});
    cactus.vertexes[6].push_back(vpos{1, 0, 0.0625f});

    cactus.vertexes[6].push_back(vpos{0, 1, 0.9375f});
    cactus.vertexes[6].push_back(vpos{0, 0, 0.9375f});
    cactus.vertexes[6].push_back(vpos{1, 1, 0.9375f});
    cactus.vertexes[6].push_back(vpos{1, 1, 0.9375f});
    cactus.vertexes[6].push_back(vpos{0, 0, 0.9375f});
    cactus.vertexes[6].push_back(vpos{1, 0, 0.9375f});

    cactus.uv[6].push_back(uvpos{1, 0});
    cactus.uv[6].push_back(uvpos{0, 0});
    cactus.uv[6].push_back(uvpos{1, 1});
    cactus.uv[6].push_back(uvpos{0, 0});
    cactus.uv[6].push_back(uvpos{0, 1});
    cactus.uv[6].push_back(uvpos{1, 1});

    cactus.uv[6].push_back(uvpos{0, 0});
    cactus.uv[6].push_back(uvpos{0, 1});
    cactus.uv[6].push_back(uvpos{1, 0});
    cactus.uv[6].push_back(uvpos{1, 1});
    cactus.uv[6].push_back(uvpos{1, 0});
    cactus.uv[6].push_back(uvpos{0, 1});

    cactus.uv[2].push_back(uvpos{0, 0});
    cactus.uv[2].push_back(uvpos{1, 0});
    cactus.uv[2].push_back(uvpos{1, 1});
    cactus.uv[2].push_back(uvpos{0, 0});
    cactus.uv[2].push_back(uvpos{1, 1});
    cactus.uv[2].push_back(uvpos{0, 1});

    cactus.uv[3].push_back(uvpos{1, 0});
    cactus.uv[3].push_back(uvpos{0, 0});
    cactus.uv[3].push_back(uvpos{1, 1});
    cactus.uv[3].push_back(uvpos{1, 1});
    cactus.uv[3].push_back(uvpos{0, 0});
    cactus.uv[3].push_back(uvpos{0, 1});

    cactus.uv[6].push_back(uvpos{0, 0});
    cactus.uv[6].push_back(uvpos{0, 1});
    cactus.uv[6].push_back(uvpos{1, 1});
    cactus.uv[6].push_back(uvpos{0, 0});
    cactus.uv[6].push_back(uvpos{1, 1});
    cactus.uv[6].push_back(uvpos{1, 0});

    cactus.uv[6].push_back(uvpos{1, 1});
    cactus.uv[6].push_back(uvpos{1, 0});
    cactus.uv[6].push_back(uvpos{0, 1});
    cactus.uv[6].push_back(uvpos{0, 1});
    cactus.uv[6].push_back(uvpos{1, 0});
    cactus.uv[6].push_back(uvpos{0, 0});

    for (int a = 0; a < 6; a++)
        cactus.normals.push_back(sidenormals[0]);
    for (int a = 0; a < 6; a++)
        cactus.normals.push_back(sidenormals[1]);
    for (int a = 0; a < 6; a++)
        cactus.normals.push_back(sidenormals[4]);
    for (int a = 0; a < 6; a++)
        cactus.normals.push_back(sidenormals[5]);

    cactus.hasanyways = true;

    tileshapes.push_back(cactus);
}

void tiledata::addblock(ctilepos cpos, tileid id, uint32_t bshape, uint8_t tilesides, uint8_t sunlight, rgbcolor255 light, chunkmesh& cmesh)
{
    if (!tileshapes[bshape].onlyanyways)
    {
        for (int a = 0; a < 6; a++)
        {
            if (tilesidevalues[a] & tilesides)
            {
                int index = 0;
                for (vpos& v : tileshapes[bshape].vertexes[a])
                {
                    uint32_t texid = gettileinfo(id).sidetextureids[a];
                    cmesh.addvertex(vpos{cpos.x + v.x, cpos.y + v.y, cpos.z + v.z}, sidenormals[a], tileshapes[bshape].uv[a][index], texid, sunlight, light);
                    index ++;
                }
            }
        }
    }
    if (tileshapes[bshape].hasanyways)
    {
        int index = 0;
        for (vpos& v : tileshapes[bshape].vertexes[6])
        {
            uint32_t texid = gettileinfo(id).sidetextureids[0];
            cmesh.addvertex(vpos{cpos.x + v.x, cpos.y + v.y, cpos.z + v.z}, tileshapes[bshape].normals[index], tileshapes[bshape].uv[6][index], texid, sunlight, light);
            index ++;
        }
    }
}
