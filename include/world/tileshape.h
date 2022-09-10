#ifndef TILESHAPE_H
#define TILESHAPE_H


class tileshape
{
    public:
        tileshape();
        virtual ~tileshape();

        bool onlyanyways {false};
        bool hasanyways {false};

        bool hasside[7] {false, false, false, false, false, false, false};

        std::vector<vpos> vertexes[7]; //sides 0-6 = XM, XP, YM, YP, ZM, ZP, anywayz
        std::vector<uvpos> uv[7];

        std::vector<vnorm> normals; //for 7 (anyways) only
        std::vector<uint8_t> slsides; //for 7 only

    protected:

    private:
};

#endif // TILESHAPE_H
