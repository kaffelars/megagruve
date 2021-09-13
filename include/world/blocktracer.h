#ifndef BLOCKTRACER_H
#define BLOCKTRACER_H


namespace blocktracer
{
    struct hitblock
    {
        chunkpos cpos {chunkpos{0,0}};
        ctilepos ctpos {ctilepos{0,-1,0}};
        tilesideid hitside {tilesideid::xm};
    };

    hitblock traceblocks(wposition startposition, direction tracedirection, float maxdistance);
};

#endif // BLOCKTRACER_H
