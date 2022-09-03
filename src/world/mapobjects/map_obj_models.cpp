#include "consts.h"
#include "map_obj_models.h"

#include "map_obj_model.h"
#include "texturemanager.h"

namespace map_obj_models
{
    std::vector<map_obj_model> obj_models;
    vnorm rotatenormal(vnorm n, uint8_t forwardside);
    vpos rotatevertexes(vpos v, uint8_t forwardside);
}

void map_obj_models::initialize()
{
    vnorm chestnormals[7] = {vnorm{-1,0,0}, vnorm{1,0,0}, vnorm{0,-1,0}, vnorm{0,1,0}, vnorm{0,-1,0}, vnorm{0,0,-1}, vnorm{0,0,1}};
    vnorm sidenormals[6] = {vnorm{-1,0,0}, vnorm{1,0,0}, vnorm{0,-1,0}, vnorm{0,1,0}, vnorm{0,0,-1}, vnorm{0,0,1}};

    //chest
    map_obj_model t;

    t.vertexes.push_back(vpos{0.0625f, 0.125f, 0.0625f});
    t.vertexes.push_back(vpos{0.0625f, 0.125f, 0.9375f});
    t.vertexes.push_back(vpos{0.0625f, 1.0f, 0.0625f});
    t.vertexes.push_back(vpos{0.0625f, 0.125f, 0.9375f});
    t.vertexes.push_back(vpos{0.0625f, 1.0f, 0.9375f});
    t.vertexes.push_back(vpos{0.0625f, 1.0f, 0.0625f});

    t.vertexes.push_back(vpos{0.9375f, 0.125f, 0.0625f});
    t.vertexes.push_back(vpos{0.9375f, 1.0f, 0.0625f});
    t.vertexes.push_back(vpos{0.9375f, 0.125f, 0.9375f});
    t.vertexes.push_back(vpos{0.9375f, 1.0f, 0.9375f});
    t.vertexes.push_back(vpos{0.9375f, 0.125f, 0.9375f});
    t.vertexes.push_back(vpos{0.9375f, 1.0f, 0.0625f});

    t.vertexes.push_back(vpos{0.0625f, 0.125f, 0.0625f}); //12 top
    t.vertexes.push_back(vpos{0.9375f, 0.125f, 0.0625f}); //13
    t.vertexes.push_back(vpos{0.9375f, 0.125f, 0.9375f}); //14
    t.vertexes.push_back(vpos{0.0625f, 0.125f, 0.0625f}); //15
    t.vertexes.push_back(vpos{0.9375f, 0.125f, 0.9375f}); //16
    t.vertexes.push_back(vpos{0.0625f, 0.125f, 0.9375f}); //17

    t.vertexes.push_back(vpos{0.9375f, 1.0f, 0.0625f}); //bottom
    t.vertexes.push_back(vpos{0.0625f, 1.0f, 0.0625f});
    t.vertexes.push_back(vpos{0.9375f, 1.0f, 0.9375f});
    t.vertexes.push_back(vpos{0.9375f, 1.0f, 0.9375f});
    t.vertexes.push_back(vpos{0.0625f, 1.0f, 0.0625f});
    t.vertexes.push_back(vpos{0.0625f, 1.0f, 0.9375f});

    t.vertexes.push_back(vpos{0.0625f, 0.145f, 0.0625f}); //inside
    t.vertexes.push_back(vpos{0.9375f, 0.145f, 0.0625f});
    t.vertexes.push_back(vpos{0.9375f, 0.145f, 0.9375f});
    t.vertexes.push_back(vpos{0.0625f, 0.145f, 0.0625f});
    t.vertexes.push_back(vpos{0.9375f, 0.145f, 0.9375f});
    t.vertexes.push_back(vpos{0.0625f, 0.145f, 0.9375f});


    t.vertexes.push_back(vpos{0.0625f, 0.125f, 0.0625f});
    t.vertexes.push_back(vpos{0.0625f, 1.0f, 0.0625f});
    t.vertexes.push_back(vpos{0.9375f, 1.0f, 0.0625f});
    t.vertexes.push_back(vpos{0.0625f, 0.125f, 0.0625f});
    t.vertexes.push_back(vpos{0.9375f, 1.0f, 0.0625f});
    t.vertexes.push_back(vpos{0.9375f, 0.125f, 0.0625f});

    t.vertexes.push_back(vpos{0.0625f, 1.0f, 0.9375f});
    t.vertexes.push_back(vpos{0.0625f, 0.125f, 0.9375f});
    t.vertexes.push_back(vpos{0.9375f, 1.0f, 0.9375f});
    t.vertexes.push_back(vpos{0.9375f, 1.0f, 0.9375f});
    t.vertexes.push_back(vpos{0.0625f, 0.125f, 0.9375f});
    t.vertexes.push_back(vpos{0.9375f, 0.125f, 0.9375f});

    t.uv.push_back(uvpos{1, 0});
    t.uv.push_back(uvpos{0, 0});
    t.uv.push_back(uvpos{1, 1});
    t.uv.push_back(uvpos{0, 0});
    t.uv.push_back(uvpos{0, 1});
    t.uv.push_back(uvpos{1, 1});

    t.uv.push_back(uvpos{0, 0});
    t.uv.push_back(uvpos{0, 1});
    t.uv.push_back(uvpos{1, 0});
    t.uv.push_back(uvpos{1, 1});
    t.uv.push_back(uvpos{1, 0});
    t.uv.push_back(uvpos{0, 1});

    t.uv.push_back(uvpos{0, 0});
    t.uv.push_back(uvpos{0, 1});
    t.uv.push_back(uvpos{1, 1});
    t.uv.push_back(uvpos{0, 0});
    t.uv.push_back(uvpos{1, 1});
    t.uv.push_back(uvpos{1, 0});

    t.uv.push_back(uvpos{1, 0});
    t.uv.push_back(uvpos{0, 0});
    t.uv.push_back(uvpos{1, 1});
    t.uv.push_back(uvpos{1, 1});
    t.uv.push_back(uvpos{0, 0});
    t.uv.push_back(uvpos{0, 1});

    t.uv.push_back(uvpos{0, 0}); //chest inside
    t.uv.push_back(uvpos{0, 1});
    t.uv.push_back(uvpos{1, 1});
    t.uv.push_back(uvpos{0, 0});
    t.uv.push_back(uvpos{1, 1});
    t.uv.push_back(uvpos{1, 0});

    t.uv.push_back(uvpos{0, 0});
    t.uv.push_back(uvpos{0, 1});
    t.uv.push_back(uvpos{1, 1});
    t.uv.push_back(uvpos{0, 0});
    t.uv.push_back(uvpos{1, 1});
    t.uv.push_back(uvpos{1, 0});

    t.uv.push_back(uvpos{1, 1});
    t.uv.push_back(uvpos{1, 0});
    t.uv.push_back(uvpos{0, 1});
    t.uv.push_back(uvpos{0, 1});
    t.uv.push_back(uvpos{1, 0});
    t.uv.push_back(uvpos{0, 0});

    for (uvpos& uv : t.uv)
    {
        if (uv.x == 0.0f) uv.x = 0.0625f;
        if (uv.y == 0.0f) uv.y = 0.0625f;
        if (uv.x == 1.0f) uv.x = 0.9375f;
        if (uv.y == 1.0f) uv.y = 0.9375f;
    }

    tileid texids[7] = {texturemanager::gettiletexturenumber("chest_front"), texturemanager::gettiletexturenumber("chest_side"), texturemanager::gettiletexturenumber("chest_top"),
    texturemanager::gettiletexturenumber("chest_bottom"),texturemanager::gettiletexturenumber("chest_inside"), texturemanager::gettiletexturenumber("chest_side"), texturemanager::gettiletexturenumber("chest_side")};

    for (int a = 0; a < 7; a++)
    {
        for (int b = 0; b < 6; b++)
        {
            t.normals.push_back(chestnormals[a]);
            t.texids.push_back(texids[a]);
            t.glow.push_back(0);
        }
    }

    obj_models.push_back(t);


    t.vertexes[12].y -= 0.125f;
    t.vertexes[15].y -= 0.125f;
    t.vertexes[17].y -= 0.125f;

    obj_models.push_back(t);

    t.vertexes[12].y += 0.125f;
    t.vertexes[15].y += 0.125f;
    t.vertexes[17].y += 0.125f;


    //flagpole
    map_obj_model f;

    for (int y = 0; y < 11; y++)
    {
        f.vertexes.push_back(vpos{0.0625f, 0.0f - y, 0.0625f});
        f.vertexes.push_back(vpos{0.0625f, 0.0f - y, 0.9375f});
        f.vertexes.push_back(vpos{0.0625f, 1.0f - y, 0.0625f});
        f.vertexes.push_back(vpos{0.0625f, 0.0f - y, 0.9375f});
        f.vertexes.push_back(vpos{0.0625f, 1.0f - y, 0.9375f});
        f.vertexes.push_back(vpos{0.0625f, 1.0f - y, 0.0625f});

        f.vertexes.push_back(vpos{0.9375f, 0.0f - y, 0.0625f});
        f.vertexes.push_back(vpos{0.9375f, 1.0f - y, 0.0625f});
        f.vertexes.push_back(vpos{0.9375f, 0.0f - y, 0.9375f});
        f.vertexes.push_back(vpos{0.9375f, 1.0f - y, 0.9375f});
        f.vertexes.push_back(vpos{0.9375f, 0.0f - y, 0.9375f});
        f.vertexes.push_back(vpos{0.9375f, 1.0f - y, 0.0625f});

        f.vertexes.push_back(vpos{0.0625f, 0.0f - y, 0.0625f});
        f.vertexes.push_back(vpos{0.0625f, 1.0f - y, 0.0625f});
        f.vertexes.push_back(vpos{0.9375f, 1.0f - y, 0.0625f});
        f.vertexes.push_back(vpos{0.0625f, 0.0f - y, 0.0625f});
        f.vertexes.push_back(vpos{0.9375f, 1.0f - y, 0.0625f});
        f.vertexes.push_back(vpos{0.9375f, 0.0f - y, 0.0625f});

        f.vertexes.push_back(vpos{0.0625f, 1.0f - y, 0.9375f});
        f.vertexes.push_back(vpos{0.0625f, 0.0f - y, 0.9375f});
        f.vertexes.push_back(vpos{0.9375f, 1.0f - y, 0.9375f});
        f.vertexes.push_back(vpos{0.9375f, 1.0f - y, 0.9375f});
        f.vertexes.push_back(vpos{0.0625f, 0.0f - y, 0.9375f});
        f.vertexes.push_back(vpos{0.9375f, 0.0f - y, 0.9375f});

        f.uv.push_back(uvpos{1, 0});
        f.uv.push_back(uvpos{0, 0});
        f.uv.push_back(uvpos{1, 1});
        f.uv.push_back(uvpos{0, 0});
        f.uv.push_back(uvpos{0, 1});
        f.uv.push_back(uvpos{1, 1});

        f.uv.push_back(uvpos{0, 0});
        f.uv.push_back(uvpos{0, 1});
        f.uv.push_back(uvpos{1, 0});
        f.uv.push_back(uvpos{1, 1});
        f.uv.push_back(uvpos{1, 0});
        f.uv.push_back(uvpos{0, 1});

        f.uv.push_back(uvpos{0, 0});
        f.uv.push_back(uvpos{0, 1});
        f.uv.push_back(uvpos{1, 1});
        f.uv.push_back(uvpos{0, 0});
        f.uv.push_back(uvpos{1, 1});
        f.uv.push_back(uvpos{1, 0});

        f.uv.push_back(uvpos{1, 1});
        f.uv.push_back(uvpos{1, 0});
        f.uv.push_back(uvpos{0, 1});
        f.uv.push_back(uvpos{0, 1});
        f.uv.push_back(uvpos{1, 0});
        f.uv.push_back(uvpos{0, 0});

        tileid texid = texturemanager::gettiletexturenumber("flagpole");

        for (int a = 0; a < 6; a++)
        {
            if (a != 2 && a != 3)
            {
                for (int b = 0; b < 6; b++)
                {
                    f.normals.push_back(sidenormals[a]);
                    f.texids.push_back(texid);
                    f.glow.push_back(0);
                }
            }
        }
    }

    for (vpos& v : f.vertexes)
    {
        if (v.x == 0.0625f) v.x = 0.375f;
        if (v.z == 0.0625f) v.z = 0.375f;
        if (v.x == 0.9375f) v.x = 0.625f;
        if (v.z == 0.9375f) v.z = 0.625f;
    }

    /*for (uvpos& uv : f.uv)
    {
        if (uv.x == 0.0f) uv.x = 0.375f;
        if (uv.y == 0.0f) uv.y = 0.375f;
        if (uv.x == 1.0f) uv.x = 0.625f;
        if (uv.y == 1.0f) uv.y = 0.625f;
    }*/

    obj_models.push_back(f);


    //flag
    map_obj_model ff;

    int y = 10;

    ff.vertexes.push_back(vpos{-0.625f, 0.0f , 0.5f});
    ff.vertexes.push_back(vpos{-0.625f, 1.0f , 0.5f});
    ff.vertexes.push_back(vpos{0.375f, 1.0f , 0.5f});
    ff.vertexes.push_back(vpos{-0.625f, 0.0f , 0.5f});
    ff.vertexes.push_back(vpos{0.375f, 1.0f , 0.5f});
    ff.vertexes.push_back(vpos{0.375f, 0.0f , 0.5f});

    ff.vertexes.push_back(vpos{-0.625f, 1.0f , 0.5f});
    ff.vertexes.push_back(vpos{-0.625f, 0.0f , 0.5f});
    ff.vertexes.push_back(vpos{0.375f, 1.0f , 0.5f});
    ff.vertexes.push_back(vpos{0.375f, 1.0f , 0.5f});
    ff.vertexes.push_back(vpos{-0.625f, 0.0f , 0.5f});
    ff.vertexes.push_back(vpos{0.375f, 0.0f , 0.5f});


    for (vpos& v: ff.vertexes)
    {
        if (v.x == -0.625f) v.x -= 1.0f;
        v.y *= 2;
        v.y -= y;
    }

    ff.uv.push_back(uvpos{1, 0});
    ff.uv.push_back(uvpos{1, 1});
    ff.uv.push_back(uvpos{0, 1});
    ff.uv.push_back(uvpos{1, 0});
    ff.uv.push_back(uvpos{0, 1});
    ff.uv.push_back(uvpos{0, 0});

    ff.uv.push_back(uvpos{1, 1});
    ff.uv.push_back(uvpos{1, 0});
    ff.uv.push_back(uvpos{0, 1});
    ff.uv.push_back(uvpos{0, 1});
    ff.uv.push_back(uvpos{1, 0});
    ff.uv.push_back(uvpos{0, 0});

    tileid texid = texturemanager::gettiletexturenumber("flag1");

    for (int b = 0; b < 6; b++)
    {
        ff.normals.push_back(sidenormals[4]);
        ff.texids.push_back(texid);
        ff.glow.push_back(0);
    }
    for (int b = 0; b < 6; b++)
    {
        ff.normals.push_back(sidenormals[5]);
        ff.texids.push_back(texid);
        ff.glow.push_back(0);
    }

    obj_models.push_back(ff);


    map_obj_model table;

    int i = 0;
    while (true)
    {
        if (i == 18) i+= 6;
        if (i == 36) break;

        table.vertexes.push_back(t.vertexes[i]);
        table.uv.push_back(t.uv[i]);
        table.normals.push_back(t.normals[i]);
        table.glow.push_back(0);

        i++;
    }

    texid = texturemanager::gettiletexturenumber("crafting_table");
    tileid texid2 = texturemanager::gettiletexturenumber("table_side");

    for (int b = 0; b < 12; b++)
    {
        table.texids.push_back(texid2);
    }
    for (int b = 0; b < 6; b++)
    {
        table.texids.push_back(texid);
    }
    for (int b = 0; b < 12; b++)
    {
        table.texids.push_back(texid2);
    }

    obj_models.push_back(table);


    map_obj_model door;

    texid = texturemanager::gettiletexturenumber("door_upper");
    texid2 = texturemanager::gettiletexturenumber("door_lower");

    float th = 0.05f;

    door.vertexes.push_back(vpos{0.5f-th, 0, 0});
    door.vertexes.push_back(vpos{0.5f-th, 0, 1});
    door.vertexes.push_back(vpos{0.5f-th, 1, 0});
    door.vertexes.push_back(vpos{0.5f-th, 0, 1});
    door.vertexes.push_back(vpos{0.5f-th, 1, 1});
    door.vertexes.push_back(vpos{0.5f-th, 1, 0});

    door.vertexes.push_back(vpos{0.5f+th, 0, 0});
    door.vertexes.push_back(vpos{0.5f+th, 1, 0});
    door.vertexes.push_back(vpos{0.5f+th, 0, 1});
    door.vertexes.push_back(vpos{0.5f+th, 1, 1});
    door.vertexes.push_back(vpos{0.5f+th, 0, 1});
    door.vertexes.push_back(vpos{0.5f+th, 1, 0});

    door.vertexes.push_back(vpos{0.5f-th, 0, 0});
    door.vertexes.push_back(vpos{0.5f-th, 1, 0});
    door.vertexes.push_back(vpos{0.5f+th, 1, 0});
    door.vertexes.push_back(vpos{0.5f-th, 0, 0});
    door.vertexes.push_back(vpos{0.5f+th, 1, 0});
    door.vertexes.push_back(vpos{0.5f+th, 0, 0});

    door.vertexes.push_back(vpos{0.5f-th, 1, 1});
    door.vertexes.push_back(vpos{0.5f-th, 0, 1});
    door.vertexes.push_back(vpos{0.5f+th, 1, 1});
    door.vertexes.push_back(vpos{0.5f+th, 1, 1});
    door.vertexes.push_back(vpos{0.5f-th, 0, 1});
    door.vertexes.push_back(vpos{0.5f+th, 0, 1});

    door.uv.push_back(uvpos{1, 0});
    door.uv.push_back(uvpos{0, 0});
    door.uv.push_back(uvpos{1, 1});
    door.uv.push_back(uvpos{0, 0});
    door.uv.push_back(uvpos{0, 1});
    door.uv.push_back(uvpos{1, 1});

    door.uv.push_back(uvpos{1, 0});
    door.uv.push_back(uvpos{1, 1});
    door.uv.push_back(uvpos{0, 0});
    door.uv.push_back(uvpos{0, 1});
    door.uv.push_back(uvpos{0, 0});
    door.uv.push_back(uvpos{1, 1});

    door.uv.push_back(uvpos{0, 0});
    door.uv.push_back(uvpos{0, 1});
    door.uv.push_back(uvpos{0.1f, 1});
    door.uv.push_back(uvpos{0, 0});
    door.uv.push_back(uvpos{0.1f, 1});
    door.uv.push_back(uvpos{0.1f, 0});

    door.uv.push_back(uvpos{0.1f, 1});
    door.uv.push_back(uvpos{0.1f, 0});
    door.uv.push_back(uvpos{0, 1});
    door.uv.push_back(uvpos{0, 1});
    door.uv.push_back(uvpos{0.1f, 0});
    door.uv.push_back(uvpos{0, 0});

    for (int a = 0; a < 24; a++)
    {
        door.texids.push_back(texid2);
        vpos v = door.vertexes[a];
        uvpos u = door.uv[a];
        v.y -= 1;
        door.vertexes.push_back(v);
        door.uv.push_back(u);
        door.glow.push_back(0);
    }
    for (int a = 0; a < 24; a++)
    {
        door.texids.push_back(texid);
        door.glow.push_back(0);
    }

    for (int b = 0; b < 2; b++)
    {
        for (int a = 0; a < 6; a++)
            door.normals.push_back(sidenormals[0]);
        for (int a = 0; a < 6; a++)
            door.normals.push_back(sidenormals[1]);
        for (int a = 0; a < 6; a++)
            door.normals.push_back(sidenormals[4]);
        for (int a = 0; a < 6; a++)
            door.normals.push_back(sidenormals[5]);
    }


    obj_models.push_back(door);

    glm::mat4 rotmat = glm::rotate(glm::mat4(1.0f), 1.5f, glm::vec3(0,1,0));

    for (int a = 0; a < 48; a++)
    {
        vpos v = door.vertexes[a];
        v.x -= 0.5f;
        glm::vec4 rotv = glm::vec4(v.x, v.y, v.z, 1.0f);
        rotv = rotmat * rotv;
        rotv.x += 0.5f;

        door.vertexes[a] = glm::vec3(rotv.x, rotv.y, rotv.z);

        v = door.normals[a];
        rotv = glm::vec4(v.x, v.y, v.z, 1.0f);
        rotv = rotmat * rotv;
        door.normals[a] = glm::vec3(rotv.x, rotv.y, rotv.z);
    }

    obj_models.push_back(door);//opendoor

    map_obj_model button;

    button.vertexes.push_back(vpos{0, 0, 0});
    button.vertexes.push_back(vpos{0, 0, 1});
    button.vertexes.push_back(vpos{0, 1, 0});
    button.vertexes.push_back(vpos{0, 0, 1});
    button.vertexes.push_back(vpos{0, 1, 1});
    button.vertexes.push_back(vpos{0, 1, 0});

    /*button.vertexes.push_back(vpos{1, 0, 0});
    button.vertexes.push_back(vpos{1, 1, 0});
    button.vertexes.push_back(vpos{1, 0, 1});
    button.vertexes.push_back(vpos{1, 1, 1});
    button.vertexes.push_back(vpos{1, 0, 1});
    button.vertexes.push_back(vpos{1, 1, 0});*/

    button.vertexes.push_back(vpos{0, 0, 0});
    button.vertexes.push_back(vpos{1, 0, 0});
    button.vertexes.push_back(vpos{1, 0, 1});
    button.vertexes.push_back(vpos{0, 0, 0});
    button.vertexes.push_back(vpos{1, 0, 1});
    button.vertexes.push_back(vpos{0, 0, 1});

    button.vertexes.push_back(vpos{1, 1, 0});
    button.vertexes.push_back(vpos{0, 1, 0});
    button.vertexes.push_back(vpos{1, 1, 1});
    button.vertexes.push_back(vpos{1, 1, 1});
    button.vertexes.push_back(vpos{0, 1, 0});
    button.vertexes.push_back(vpos{0, 1, 1});

    button.vertexes.push_back(vpos{0, 0, 0});
    button.vertexes.push_back(vpos{0, 1, 0});
    button.vertexes.push_back(vpos{1, 1, 0});
    button.vertexes.push_back(vpos{0, 0, 0});
    button.vertexes.push_back(vpos{1, 1, 0});
    button.vertexes.push_back(vpos{1, 0, 0});

    button.vertexes.push_back(vpos{0, 1, 1});
    button.vertexes.push_back(vpos{0, 0, 1});
    button.vertexes.push_back(vpos{1, 1, 1});
    button.vertexes.push_back(vpos{1, 1, 1});
    button.vertexes.push_back(vpos{0, 0, 1});
    button.vertexes.push_back(vpos{1, 0, 1});

    for (vpos& v: button.vertexes)
    {
        if (v.x == 0) v.x = 0.7f;
        if (v.y == 0) v.y = 0.4f;
        if (v.y == 1) v.y = 0.6f;
        if (v.z == 0) v.z = 0.4f;
        if (v.z == 1) v.z = 0.6f;
    }

    button.uv.push_back(uvpos{1, 0});
    button.uv.push_back(uvpos{0, 0});
    button.uv.push_back(uvpos{1, 1});
    button.uv.push_back(uvpos{0, 0});
    button.uv.push_back(uvpos{0, 1});
    button.uv.push_back(uvpos{1, 1});

    /*button.uv.push_back(uvpos{0, 0});
    button.uv.push_back(uvpos{0, 1});
    button.uv.push_back(uvpos{1, 0});
    button.uv.push_back(uvpos{1, 1});
    button.uv.push_back(uvpos{1, 0});
    button.uv.push_back(uvpos{0, 1});*/

    button.uv.push_back(uvpos{0, 0});
    button.uv.push_back(uvpos{0, 1});
    button.uv.push_back(uvpos{1, 1});
    button.uv.push_back(uvpos{0, 0});
    button.uv.push_back(uvpos{1, 1});
    button.uv.push_back(uvpos{1, 0});

    button.uv.push_back(uvpos{1, 0});
    button.uv.push_back(uvpos{0, 0});
    button.uv.push_back(uvpos{1, 1});
    button.uv.push_back(uvpos{1, 1});
    button.uv.push_back(uvpos{0, 0});
    button.uv.push_back(uvpos{0, 1});

    button.uv.push_back(uvpos{0, 0});
    button.uv.push_back(uvpos{0, 1});
    button.uv.push_back(uvpos{1, 1});
    button.uv.push_back(uvpos{0, 0});
    button.uv.push_back(uvpos{1, 1});
    button.uv.push_back(uvpos{1, 0});

    button.uv.push_back(uvpos{1, 1});
    button.uv.push_back(uvpos{1, 0});
    button.uv.push_back(uvpos{0, 1});
    button.uv.push_back(uvpos{0, 1});
    button.uv.push_back(uvpos{1, 0});
    button.uv.push_back(uvpos{0, 0});

    texid = texturemanager::gettiletexturenumber("planks");

    for (int a = 0; a < 6; a++)
    {
        if (a != 1)
        {
            for (int b = 0; b < 6; b++)
            {
                button.normals.push_back(sidenormals[a]);
                button.texids.push_back(texid);
                button.glow.push_back(0);
            }
        }
    }

    obj_models.push_back(button); //7



    texid = texturemanager::gettiletexturenumber("lightbulb");

    for (vpos& v : button.vertexes)
    {
        if (v.x == 0.7f) v.x = 0.8f;
    }

    for (tileid& tid : button.texids)
        tid = texid;
    for (uint8_t& glow : button.glow)
        glow = 128;

    for (uvpos& uv:button.uv)
    {
        if (uv.x == 0) uv.x = 0.2f; //0.1875f;
        if (uv.x == 1) uv.x = 0.8f; //0.8125f;
        if (uv.y == 0) uv.y = 0.2f; //0.1875f;
        if (uv.y == 1) uv.y = 0.8f; //0.8125f;
    }

    obj_models.push_back(button); //lightbulb 8
}

void map_obj_models::addmodel(chunkmesh& cm, ctilepos ctpos, uint32_t modelid, uint8_t forwardside, int32_t texid)
{
    for (int i = 0; i < obj_models[modelid].vertexes.size(); i++)
    {
        int index = i;
        if (forwardside == 4 || forwardside == 5) //fixe inverted sides på z sides
        {
            if (i % 3 == 0) index = i + 1;
            if ((i-1) % 3 == 0) index = i - 1;
        }
        vpos vp = rotatevertexes(obj_models[modelid].vertexes[index], forwardside);
        vp.x += ctpos.x;
        vp.y += ctpos.y;
        vp.z += ctpos.z;
        vnorm n = rotatenormal(obj_models[modelid].normals[index], forwardside);

        int32_t textureid = obj_models[modelid].texids[index];
        if (texid != -1) textureid = texid;

        //std::cout << "hamberder " << texid << "\n";

        cm.addvertex(vp, n, obj_models[modelid].uv[index], textureid, 255, notint, obj_models[modelid].glow[index], 0.0f, notint);//sunlight[corner], light[corner], glow, ambocc[corner], notint);
    }
}

vpos map_obj_models::rotatevertexes(vpos v, uint8_t forwardside)
{
    switch(forwardside)
    {
    case 0:
        return v;
    case 1:
        return vpos{-v.x + 1.0f, v.y, -v.z + 1.0f};
    case 2:
        return vpos{v.y, v.x, -v.z + 1.0f};
    case 3:
        return vpos{v.y, -v.x + 1.0f, v.z};
    case 4:
        return vpos{v.z, v.y, v.x};
    case 5:
        return vpos{-v.z + 1.0f, v.y, -v.x + 1.0f};
    default:
        //burde ikke skje
        break;
    }
}

vnorm map_obj_models::rotatenormal(vnorm n, uint8_t forwardside)
{
    switch(forwardside) //noe er galt - kanskje ikke
    {
    case 0:
        return n;
    case 1:
        n.x = -n.x;
        n.z = -n.z;
        return n;
    case 2:
        {
            float g = n.x;
            n.x = n.y;
            n.y = g;
            n.z = -n.z;
        }
    case 3:
        {
            float g = n.x;
            n.x = n.y;
            n.y = -g;
        }
    case 4:
        {
            float g = n.x;
            n.x = n.z;
            n.z = g;
            return n;
        }
    case 5:
        {
            float g = n.x;
            n.x = -n.z;
            n.z = -g;
            return n;
        }
    default:
        //burde ikke skje
        break;
    }

    return n;
}
