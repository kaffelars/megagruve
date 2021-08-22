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

void chunkmesh::addvertex(vpos pos, vnorm norm, uvpos uv, textureid tid, uint8_t sunlight, rgbcolor255 light, uint8_t glow, uint8_t ambocc, rgbcolor255 tint)
{
    float uvtex = utils::packu2f(uv.x*255.0f, uv.y*255.0f, tid);
    float packednorm = utils::packnormal(norm.x, norm.y, norm.z);
    float packedlight = utils::packu2f(light.x, light.y, light.z);
    float packeddiv = utils::packu2f(sunlight, ambocc, glow);
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
    glDeleteBuffers(2, vbo);

    glDeleteVertexArrays(1, vao);
}

void chunkmesh::cleanall() //renser alt
{
    if (!isempty())
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
    if (!isempty())
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(vao[0]);

        glDrawArrays(GL_TRIANGLES, 0, vertexes[0].size()/4);
    }
}
