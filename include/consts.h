#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED


#define GL3_PROTOTYPES 1


#include "includes.h"


constexpr float pi_value = 3.1415926535f;
constexpr int chunkwidth = 32;
constexpr int chunkheight = 256;
constexpr int chunkmeshheight = 64;
constexpr int chunkmeshynum = chunkheight/chunkmeshheight;

//constexpr int maxthreads = 3;

#include "enumclasses.h"
#include "aliases.h"

const glm::ivec3 sideoffsets[6] = {glm::ivec3(-1, 0 ,0), glm::ivec3(1, 0 ,0), glm::ivec3(0, -1 ,0), glm::ivec3(0, 1 ,0), glm::ivec3(0, 0 ,-1), glm::ivec3(0, 0 ,1)};
const rgbcolor255 notint = rgbcolor255{127,127,127};
const uint8_t sideflags[6] = {1,2,4,8,16,32};

const tileid mapobjtileid = 255;

#endif // CONSTS_H_INCLUDED
