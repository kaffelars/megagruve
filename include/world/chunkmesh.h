#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include "utils.h"

class chunkmesh
{
    public:
        chunkmesh();
        virtual ~chunkmesh();

        bool setvbos();
        bool isempty();
        void cleanbuffers();
        void cleanall();
        void addvertex(vpos pos, vnorm norm, uvpos uv, textureid tid, uint8_t sunlight, rgbcolor255 light, uint8_t glow, uint8_t ambocc, rgbcolor255 tint);

        void render();


    protected:

    private:
        GLuint vbo[5] {0,0,0,0,0};
        GLuint vao[1] {0};
        std::vector<GLfloat> vertexes[2];

        bool vbosset {false};

        uint32_t vertexnum;

};

#endif // CHUNKMESH_H
