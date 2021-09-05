#ifndef MAP_OBJ_MODEL_H
#define MAP_OBJ_MODEL_H


class map_obj_model
{
    public:
        map_obj_model();
        virtual ~map_obj_model();

        std::vector<vpos> vertexes; //sides 0-6 = XM, XP, YM, YP, ZM, ZP, anywayz
        std::vector<uvpos> uv;

        std::vector<vnorm> normals;
        std::vector<tileid> texids;

    protected:

    private:
};

#endif // MAP_OBJ_MODEL_H
