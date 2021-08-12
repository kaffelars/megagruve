#ifndef TILESHAPE_H
#define TILESHAPE_H


class tileshape
{
    public:
        tileshape();
        virtual ~tileshape();

        bool onlyanyways {false};
        bool hasanyways {false};

        std::vector<vpos> vertexes[7]; //sides 0-6 = XM, XP, YM, YP, ZM, ZP, anywayz
        std::vector<uvpos> uv[7];

        std::vector<vnorm> normals; //for 7 (anyways) only

    protected:

    private:
};

#endif // TILESHAPE_H
