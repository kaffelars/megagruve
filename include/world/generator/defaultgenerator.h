#ifndef DEFAULTGENERATOR_H
#define DEFAULTGENERATOR_H

#include "chunkgenerator.h"

class defaultgenerator : public chunkgenerator
{
    public:
        defaultgenerator();
        virtual ~defaultgenerator();

        void generator(chunk& c);

    protected:

    private:
        void decorate(chunk& c);
};

#endif // DEFAULTGENERATOR_H
