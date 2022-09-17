#include "consts.h"
#include "chunkmesh.h"


chunkmesh::chunkmesh()
{
    //ctor
}

chunkmesh::~chunkmesh()
{
    //dtor
}

void chunkmesh::addvertex(vpos pos, vnorm norm, uvpos uv, textureid tid, uint8_t sunlight, uint8_t light, uint8_t glow, uint8_t ambocc, rgbcolor255 tint)
{
    float uvtex = utils::packu2f(uv.x*255.0f, uv.y*255.0f, tid);
    float packednorm = utils::packnormal(norm.x, norm.y, norm.z);
    float packedlight = utils::packu2f(sunlight, light, 0);
    float packeddiv = utils::packu2f(ambocc, glow, 0);
    float packedtint = utils::packu2f(tint.x, tint.y, tint.z);

    vertexes[0].push_back(pos.x);
    vertexes[0].push_back(pos.y);
    vertexes[0].push_back(pos.z);
    vertexes[0].push_back(uvtex);

    vertexes[1].push_back(packednorm);
    vertexes[1].push_back(packeddiv);
    vertexes[1].push_back(packedlight);
    vertexes[1].push_back(packedtint);
}

bool chunkmesh::setvbos()
{
    if (vertexes[0].size() > 0)
    {
        vertexnum = vertexes[0].size() / 4;

        if (vbosset)
        {
            cleanbuffers();
        }

        glGenBuffers(2, vbo);

        glGenVertexArrays(1, vao);
        glBindVertexArray(vao[0]);

        //1
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, vertexes[0].size() * sizeof(GLfloat), &vertexes[0][0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, vertexes[1].size() * sizeof(GLfloat), &vertexes[1][0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);


        for (int a = 0; a < 2; a++)
        {
            glEnableVertexAttribArray(a);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        vbosset = true;

        return true;
    }
    else
    {
        return false;
    }
}

bool chunkmesh::isempty()
{
    if (vertexes[0].size() > 0) return false;

    return true;
}

void chunkmesh::cleanbuffers() //renser buffere uten å slette vectorer
{
    if (vbosset)
    {
        glDeleteBuffers(2, vbo);
        glDeleteVertexArrays(1, vao);
        vbosset = false;
    }
}

void chunkmesh::cleanall() //renser alt
{
    if (vbosset)
    {
        cleanbuffers();
        for (int a = 0; a < 2; a++)
        {
            vertexes[a].clear();
        }
    }
}

void chunkmesh::render()
{
    if (vbosset && !isempty())
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(vao[0]);

        glDrawArrays(GL_TRIANGLES, 0, vertexnum);
    }
}
