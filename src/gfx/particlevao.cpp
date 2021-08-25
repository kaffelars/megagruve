#include "consts.h"
#include "particlevao.h"

particlevao::particlevao()
{
    vbosset = false;
}

particlevao::~particlevao()
{
    //dtor
}

void particlevao::addvalues(uint8_t numbo, float val1, float val2, float val3, float val4)
{
    vertexes[numbo].push_back(val1);
    vertexes[numbo].push_back(val2);
    vertexes[numbo].push_back(val3);
    vertexes[numbo].push_back(val4);
}

void particlevao::setvbos()
{
    if (vertexes[0].size() > 0)
    {
        glGenBuffers(2, vbo);

        glGenVertexArrays(1, vao);
        glBindVertexArray(vao[0]);

        //1
        for (int a = 0; a < 2; a++)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo[a]);
            glBufferData(GL_ARRAY_BUFFER, vertexes[a].size() * sizeof(GLfloat), &vertexes[a][0], GL_STATIC_DRAW);
            glVertexAttribPointer(a, 4, GL_FLOAT, GL_FALSE, 0, 0);
        }

        for (int a = 0; a < 2; a++)
        {
            glEnableVertexAttribArray(a);
        }

        vbosset = true;
    }
}

void particlevao::cleanvbos()
{
    if (vbosset)
    {
        glDeleteBuffers(2, vbo);
        glDeleteVertexArrays(1, vao);

        for (int a = 0; a < 2; a++)
        {
            vertexes[a].clear();
        }

        vbosset = false;
    }
}

void particlevao::render()
{
    if (vbosset)
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(vao[0]);

        glDrawArrays(GL_POINTS, 0, vertexes[0].size()/4);
    }
}
