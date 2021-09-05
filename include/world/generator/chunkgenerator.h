#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H

#include "chunk.h"

class chunkgenerator
{
    public:
        chunkgenerator();
        virtual ~chunkgenerator();

        void generatechunk(chunk& c);
        void addtile(chunk& c, ctilepos ctpos, tileid tid);
        void initializechunk(chunk& c);
        void finalizechunk(chunk& c);
        void updatesunlight(chunk& c, ctilepos ctpos, bool initial);

        virtual void generator(chunk& c);
        virtual void decorate(chunk& c);
        void sethighest(chunk& c);

    protected:

    private:
};

#endif // CHUNKGENERATOR_H
