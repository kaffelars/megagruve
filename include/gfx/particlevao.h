#ifndef PARTICLEVAO_H
#define PARTICLEVAO_H


class particlevao
{
    public:
        particlevao();
        virtual ~particlevao();

        void setvbos();
        void cleanvbos();
        void render();
        void addvalues(uint8_t numbo, float val1, float val2, float val3, float val4);

    protected:

    private:
        std::vector<GLfloat> vertexes[5];
        GLuint vbo[2], vao[1];
        bool vbosset;
};

#endif // PARTICLEVAO_H
