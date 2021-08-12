#include "consts.h"
#include "vaocontainer.h"

vaocontainer::vaocontainer()
{
    //vertex pack VVVVNNNNCCCC osv. https://www.khronos.org/opengl/wiki/Vertex_Specification_Best_Practices
    vbosset = false;
    offset = glm::vec2(0, 0);
}

vaocontainer::~vaocontainer()
{
    /*if (vertexes[0].size()) //ikke ha noe her, det blir fuxor når ting flyttes rundt
    {
        cleanvbos();
    }*/
}

void vaocontainer::initialize(int numv, typo rendertyp, int ele1, int ele2, int ele3, int ele4, int ele5)
{
    rendertype = rendertyp;
    numvbos = numv;
    numelements[0] = ele1;
    numelements[1] = ele2;
    numelements[2] = ele3;
    numelements[3] = ele4;
    numelements[4] = ele5;
}

void vaocontainer::addvalues(int vertexnum, float val1, float val2, float val3, float val4)
{
    vertexes[vertexnum].push_back(val1);
    if (numelements[vertexnum]>1) vertexes[vertexnum].push_back(val2);
    if (numelements[vertexnum]>2) vertexes[vertexnum].push_back(val3);
    if (numelements[vertexnum]>3) vertexes[vertexnum].push_back(val4);
}


bool vaocontainer::setvbos()
{
    //std::cout << " v: " << vertexes[0].size() << " ";

    if (vertexes[0].size() > 0)
    {
        glGenBuffers(numvbos, vbo);

        glGenVertexArrays(1, vao);
        glBindVertexArray(vao[0]);

        //1
        for (int a = 0; a < numvbos; a++)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo[a]);
            glBufferData(GL_ARRAY_BUFFER, vertexes[a].size() * sizeof(GLfloat), &vertexes[a][0], GL_STATIC_DRAW);
            glVertexAttribPointer(a, numelements[a], GL_FLOAT, GL_FALSE, 0, 0);
        }

        for (int a = 0; a < numvbos; a++)
        {
            glEnableVertexAttribArray(a);
        }

        vbosset = true;
        return true;
    }
    else
    {
        return false;
    }
}

bool vaocontainer::isempty()
{
    if (vertexes[0].size() > 0) return false;

    return true;
}

void vaocontainer::cleanbuffers() //renser buffere uten å slette vectorer
{
    if (vbosset)
    {
        glDeleteBuffers(numvbos, vbo);

        glDeleteVertexArrays(1, vao);

        vbosset = false;
    }
}

int vaocontainer::gettrianglenumber()
{
    if (vbosset)
    {
        return vertexes[0].size() / 3;
    }
    else
    {
        return 0;
    }
}

void vaocontainer::deinit()
{
    cleanvbos();
}

void vaocontainer::cleanvbos()
{
    if (vbosset)
    {
        glDeleteBuffers(numvbos, vbo);

        glDeleteVertexArrays(1, vao);

        offset = glm::vec2(0.0f, 0.0f);

        for (int a = 0; a < numvbos; a++)
        {
            vertexes[a].clear();
        }

        vbosset = false;
    }
}

void vaocontainer::render()
{
    if (vbosset)
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(vao[0]);

        if (rendertype == typo::TRIANGLES)
            glDrawArrays(GL_TRIANGLES, 0, vertexes[0].size()/numelements[0]);

        if (rendertype == typo::POINTS)
            glDrawArrays(GL_POINTS, 0, vertexes[0].size()/numelements[0]);

        if (rendertype == typo::LINES)
            glDrawArrays(GL_LINES, 0, vertexes[0].size()/numelements[0]);

        //std::cout << vertexes[0].size() << " - " << numelements[0] << "\r\n";
    }
}
