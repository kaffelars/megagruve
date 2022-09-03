#ifndef VOXELMODEL_H
#define VOXELMODEL_H


class voxelmodel
{
    public:
        voxelmodel();
        virtual ~voxelmodel();

        struct point
        {
            ctilepos tilepos;
            tileid tid;
        };

        struct mapobject//warning: map objects cannot propagate into neighbour chunks
        {
            ctilepos tilepos;
            uint8_t mapobjid;
            uint8_t forwardside;
            int32_t extrainfo;
        };

        void addpoint(ctilepos tpos, tileid tid);
        void addmapobject(ctilepos tpos, uint8_t mapobjid, uint8_t forwardside, int32_t extrainfo);
        void centermodel();

        dimensions dims {0,0,0};
        std::vector<point> points;
        std::vector<mapobject> mapobjects;

        ctilepos centerbottomtile;

    protected:

    private:
};

#endif // VOXELMODEL_H
