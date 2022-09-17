#ifndef CHUNK_H
#define CHUNK_H

#include "tiledata.h"
#include "chunkmesh.h"
#include "shadercontroller.h"
#include "map_obj.h"
#include "mainchar.h"
#include "chunklightcontainer.h"
#include "chunklightpoints.h"

class chunk
{
    public:
        chunk(dimensions dims, chunkpos pos);
        virtual ~chunk();

        enum ctags
        {
            C_START, C_GENERATING, C_GENERATED, C_MESHING, C_MESHED, C_READY, C_REMESHING, C_REMESHED, C_KAPUT
        };

        struct tlight
        {
            uint8_t sunlight : 4;
            uint8_t light : 4;
        };

        struct biomedata
        {
            uint8_t temperature;
            uint8_t humidity;
        };

        int32_t counter{0};


        //coords
        chunkpos cpos;
        uint32_t get2dcoord(chtilepos tpos);
        uint32_t get3dcoord(ctilepos tpos);
        uint32_t gettilecoord(ctilepos tpos);
        uint32_t getbiomecoord(chtilepos thpos);
        dimensions cdims;

        //meshing
        chunkmesh cmesh[chunkmeshynum][2];
        chunkmesh wmesh[chunkmeshynum][2];
        uint8_t getactivemesh(uint8_t meshnum);
        uint8_t getinactivemesh(uint8_t meshnum);
        void toggleactivemesh(uint8_t meshnum);
        void setallvbos();
        void setonevbo(uint8_t meshnum);
        void setremeshedvbos();
        void setremesh(int toremesh, bool meshthis = true);
        void setremeshy(ytile ycoord);
        void setremeshwholechunk();
        bool getremesh(int toremesh);
        bool needsremesh();

        //tiles
        tileid gettile(ctilepos tpos);
        void settile(ctilepos tpos, tileid value);
        void trysettile(ctilepos tpos, tileid value);
        void addtile(tileid value);
        std::vector<glm::ivec4> outsidetiles[9]; //for tiles to add to neighbouring chunks (from decoration) 0 = -x,-y, 1 = 0, -y, 2 = +x, -y etc.
        bool anyoutsidetiles {false};
        void addoutsidetiles(chunkpos cpos, ctilepos ctpos, tileid tid);

        //highest - fix
        void addhighest(ytile value);
        ytile gethighest(chtilepos thpos);
        void sethighest(chtilepos thpos, ytile y);

        //biome
        void setbiome(biomedata b, chtilepos chpos);
        biomedata getbiome(chtilepos chpos);
        biomedata getbiome(ctilepos ctpos);
        void addbiome();

        //light
        void addtilelight(ctilepos ctpos, uint8_t lightstrength);
        chunklightpoints lightpoints;
        void setsunlight(ctilepos tpos, uint8_t value);
        uint8_t getsunlight(ctilepos tpos);
        uint8_t getinterpolatedsunlight(float x, float y, float z, uint8_t direction);
        uint8_t getinterpolatedsunlight2(float x, float y, float z);
        uint8_t getsunlightcorner(uint8_t x, uint8_t y, uint8_t z);
        void fillsunlayer(uint8_t layer, uint8_t value);
        tlight getalllight(ctilepos tpos);
        uint8_t gettilelightcorner(uint8_t x, uint8_t y, uint8_t z);
        void filltilelightlayer(uint8_t layer, uint8_t value);
        void settilelight(ctilepos tpos, uint8_t value);
        uint8_t gettilelight(ctilepos tpos);
        chunklightcontainer sunlight;
        chunklightcontainer tilelight;

        void render();
        void renderwater();
        void deletechunk();

        //chunk objs
        std::unordered_map<uint32_t, std::shared_ptr<map_obj>> chunk_objs;
        void addchunkobj(ctilepos ctpos, uint8_t mapobjid, uint8_t forwardside);
        void interactobj(ctilepos ctpos, mainchar& mchar);
        bool tryinteractobj(ctilepos ctpos, mainchar& mchar);
        void removechunkobj(ctilepos ctpos);
        std::shared_ptr<map_obj>& getmapobj(ctilepos ctpos);

        //threading/tags
        bool allowstilewrites();
        bool allowstilereads();
        bool isready();
        void settag(ctags tag);
        ctags gettag();
        bool safetodelete();


    protected:

    private:
        int8_t chunktagpermissions[9] = {-1, 0, 2, 1, 2, 2, 1, 2, 0};

        std::mutex tagmutex;//brukes ved lesing og setting av tags
        std::mutex remeshmutex;//brukes ved remesh
        //std::shared_mutex lock; //https://en.cppreference.com/w/cpp/thread/shared_mutex
        bool activemesh;

        std::vector<biomedata> biomes;

        std::vector<tileid> tileids;
        //std::vector<uint8_t> tilesides;
        std::vector<uint8_t> highesttile;
        //std::vector<tlight> tilelight;

        bool remesh[chunkmeshynum];


        //chunklightcontainer tilelight;


        bool activecmesh[chunkmeshynum];
        ctags chunktag {C_START};
};

#endif // CHUNK_H
