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

        void addpoint(ctilepos tpos, tileid tid);
        void centermodel();

        dimensions dims {0,0,0};
        std::vector<point> points;

        ctilepos centerbottomtile;

    protected:

    private:
};

#endif // VOXELMODEL_H
