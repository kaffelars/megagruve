#ifndef MODEL_H
#define MODEL_H


class model
{
    public:
        model();
        virtual ~model();

        struct vertex
        {
            wposition position;
            glm::vec2 uv;
            direction normal;
        };

        std::vector<vertex> vertexes;

    protected:

    private:
};

#endif // MODEL_H
