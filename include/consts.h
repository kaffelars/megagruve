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

#include <aliases.h>

const glm::ivec3 sideoffsets[6] = {glm::ivec3(-1, 0 ,0), glm::ivec3(1, 0 ,0), glm::ivec3(0, -1 ,0), glm::ivec3(0, 1 ,0), glm::ivec3(0, 0 ,-1), glm::ivec3(0, 0 ,1)};

#endif // CONSTS_H_INCLUDED
