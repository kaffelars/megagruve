#ifndef VAOCONTAINER_H
#define VAOCONTAINER_H


class vaocontainer
{
    public:
        vaocontainer();
        virtual ~vaocontainer();

        bool vbosset;

        bool isempty();

        GLuint vbo[5], vao[1];

        enum class typo {TRIANGLES, POINTS, LINES};

        typo rendertype;

        glm::vec2 offset;

        int numvbos;

        int numelements[5];

        void initialize(int numv, typo rendertyp, int ele1=4, int ele2=0, int ele3=0, int ele4=0, int ele5=0);

        std::vector<GLfloat> vertexes[5];


        std::vector<GLfloat> vertexes0;
        std::vector<GLfloat> vertexes1;
        std::vector<GLfloat> vertexes2;
        std::vector<GLfloat> vertexes3;
        std::vector<GLfloat> vertexes4;

        void deinit();

        void addvalues(int vertexes, float val1, float val2=0, float val3=0, float val4=0);


        bool setvbos();
        void cleanvbos();
        void cleanbuffers();
        void render();

        int gettrianglenumber();
    protected:
    private:
};

#endif // VAOCONTAINER_H
