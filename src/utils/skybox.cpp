#include "consts.h"
#include "skybox.h"

namespace skybox
{
    namespace
    {
        vaocontainer box;
    }
}

void skybox::render()
{
    box.render();
}

void skybox::initialize()
{
    box.cleanvbos();
    float bsize = 100.0f;

    box.initialize(1, vaocontainer::typo::TRIANGLES, 4);

    glm::vec3 norm = glm::vec3(0.0f);
    float pnorm = 0.0f;

    //norm = vec3(-1, 0, 0);
    //pnorm = utils::packnormal(norm);

    box.addvalues(0, -bsize, -bsize, bsize, pnorm);
    box.addvalues(0, -bsize, -bsize, -bsize, pnorm);
    box.addvalues(0, -bsize, bsize, bsize, pnorm);

    box.addvalues(0, -bsize, bsize, bsize, pnorm);
    box.addvalues(0, -bsize, -bsize, -bsize, pnorm);
    box.addvalues(0, -bsize, bsize, -bsize, pnorm);


    //norm = vec3(1, 0, 0);
    //pnorm = utils::packnormal(norm);

    box.addvalues(0, bsize, bsize, bsize, pnorm);
    box.addvalues(0, bsize, -bsize, -bsize, pnorm);
    box.addvalues(0, bsize, -bsize, bsize, pnorm);

    box.addvalues(0, bsize, bsize, -bsize, pnorm);
    box.addvalues(0, bsize, -bsize, -bsize, pnorm);
    box.addvalues(0, bsize, bsize, bsize, pnorm);



   // norm = vec3(0, -1, 0);
    //pnorm = utils::packnormal(norm);

    box.addvalues(0, bsize, -bsize, -bsize, pnorm);
    box.addvalues(0, -bsize, -bsize, -bsize, pnorm);
    box.addvalues(0, -bsize, -bsize, bsize, pnorm);

    box.addvalues(0, bsize, -bsize, bsize, pnorm);
    box.addvalues(0, bsize, -bsize, -bsize, pnorm);
    box.addvalues(0, -bsize, -bsize, bsize, pnorm);


    //norm = vec3(0, 1, 0);
    //pnorm = utils::packnormal(norm);

    box.addvalues(0, -bsize, bsize, bsize, pnorm);
    box.addvalues(0, -bsize, bsize, -bsize, pnorm);
    box.addvalues(0, bsize, bsize, -bsize, pnorm);

    box.addvalues(0, -bsize, bsize, bsize, pnorm);
    box.addvalues(0, bsize, bsize, -bsize, pnorm);
    box.addvalues(0, bsize, bsize, bsize, pnorm);


    //norm.z = -1;
    //pnorm = utils::packnormal(norm);

    box.addvalues(0, bsize, bsize, -bsize, pnorm);
    box.addvalues(0, -bsize, -bsize, -bsize, pnorm);
    box.addvalues(0, bsize, -bsize, -bsize, pnorm);

    box.addvalues(0, -bsize, bsize, -bsize, pnorm);
    box.addvalues(0, -bsize, -bsize, -bsize, pnorm);
    box.addvalues(0, bsize, bsize, -bsize, pnorm);

    //norm.z = 1;
    //pnorm = utils::packnormal(norm);

    box.addvalues(0, bsize, -bsize, bsize, pnorm);
    box.addvalues(0, -bsize, -bsize, bsize, pnorm);
    box.addvalues(0, bsize, bsize, bsize, pnorm);

    box.addvalues(0, bsize, bsize, bsize, pnorm);
    box.addvalues(0, -bsize, -bsize, bsize, pnorm);
    box.addvalues(0, -bsize, bsize, bsize, pnorm);



    box.setvbos();
}
