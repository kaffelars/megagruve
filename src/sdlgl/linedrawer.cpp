#include "consts.h"
#include "linedrawer.h"

namespace linedrawer
{
    namespace
    {
        //std::vector<glm::vec3> points;
        bool compiled = false;
        vaocontainer linevao;
    }
}

void linedrawer::initialize()
{
    linevao.initialize(1, vaocontainer::typo::LINES, 4);
}

void linedrawer::render(cameracontroller& camera)
{
    if (!compiled) compile();

    if (compiled)
    {
        shadercontroller::activateshader(8);//lines shader
        camera.sendmatrices(shadercontroller::getshader(8).pvmid);

        linevao.render();
    }
}

void linedrawer::clearlines()
{
    compiled = false;
    linevao.cleanvbos();
}

void linedrawer::addline(glm::vec3 start, glm::vec3 slutt, float rgb)
{
    compiled = false;
    linevao.addvalues(0, start.x, start.y, start.z, rgb);
    linevao.addvalues(0, slutt.x, slutt.y, slutt.z, rgb);
}

void linedrawer::drawrect(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float rgb)
{
    linedrawer::addline(p1, p2, rgb);
    linedrawer::addline(p2, p3, rgb);
    linedrawer::addline(p3, p4, rgb);
    linedrawer::addline(p4, p1, rgb);
}

void linedrawer::compile()
{
    if (!compiled)
    {
        if (!linevao.isempty())
        {
            compiled = true;
            linevao.setvbos();
        }
    }
}
