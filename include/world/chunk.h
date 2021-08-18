#ifndef CHUNK_H
#define CHUNK_H

#include "tiledata.h"
#include "chunkmesh.h"
#include "shadercontroller.h"

class chunk
{
    public:
        chunk(dimensions dims, chunkpos pos);
        virtual ~chunk();

        enum ctags
        {
            C_START, C_GENERATING, C_GENERATED, C_MESHING, C_MESHED, C_READY, C_REMESHING, C_REMESHED
        };

        struct tlight
        {
            uint8_t sunlight : 4;
            uint8_t light : 4;
        };

        int32_t counter{0};

        chunkpos cpos;
        chunkmesh cmesh[chunkmeshynum][2];

        inline uint32_t get2dcoord(chtilepos tpos);
        inline uint32_t get3dcoord(ctilepos tpos);
        uint32_t gettilecoord(ctilepos tpos);

        uint8_t getactivemesh(uint8_t meshnum);
        uint8_t getinactivemesh(uint8_t meshnum);
        void toggleactivemesh(uint8_t meshnum);

        void setallvbos();
        void setonevbo(uint8_t meshnum);
        void setremeshedvbos();

        bool safetodelete();

        dimensions cdims;

        void setremesh(int toremesh, bool meshthis = true);
        void setremeshy(ytile ycoord);
        bool getremesh(int toremesh);

        bool needsremesh();

        void settag(ctags tag);
        ctags gettag();

        tileid gettile(ctilepos tpos);
        void settile(ctilepos tpos, tileid value);

        uint8_t getsides(ctilepos tpos);
        void setsides(ctilepos tpos, uint8_t sideval);
        void setside(ctilepos tpos, tiledata::tilesides side, bool addside);

        void addtile(tileid value);
        void addside();
        void addside(ctilepos tpos, tiledata::tilesides side);
        void addhighest(ytile value);
        ytile gethighest(chtilepos thpos);
        void sethighest(chtilepos thpos, ytile y);

        void addlight();

        void setsunlight(ctilepos tpos, uint8_t value);
        uint8_t getsunlight(ctilepos tpos);

        void render();
        void deletechunk();

        std::vector<uint8_t> tilesides;

    protected:

    private:
        std::mutex tagmutex;//brukes ved lesing og setting av tags
        std::mutex remeshmutex;//brukes ved remesh
        std::shared_mutex lock; //https://en.cppreference.com/w/cpp/thread/shared_mutex
        bool activemesh;

        std::vector<tileid> tileids;
        //std::vector<uint8_t> tilesides;
        std::vector<uint8_t> highesttile;
        std::vector<tlight> tilelight;

        bool remesh[chunkmeshynum];


        bool activecmesh[chunkmeshynum];
        ctags chunktag {C_START};
};

#endif // CHUNK_H
