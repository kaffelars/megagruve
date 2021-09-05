#ifndef NEWGENERATOR_H
#define NEWGENERATOR_H

#include "chunkgenerator.h"

class newgenerator : public chunkgenerator
{
    public:
        newgenerator();
        virtual ~newgenerator();

        void generator(chunk& c);


    protected:

    private:
        void decorate(chunk& c);
        void generateroughland(std::vector<float>& land, chunkpos cposoffset);
        void generatebiomes(chunk& c, chunkpos cposoffset);
        void generateworld(chunk& c, std::vector<float>& land, chunkpos cposoffset);
        float getlandweight(std::vector<float>& land, ctilepos ctpos);
};

#endif // NEWGENERATOR_H
