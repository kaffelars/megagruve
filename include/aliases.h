#include "consts.h"



//aliases
using dimensions = glm::ivec3;
using tileid = uint8_t;
using textureid = uint8_t;

//i world
using wposition = glm::vec3; //en position i world 3d xyz
using hposition = glm::vec2; //en position 3d xz
using wtilepos = glm::ivec3; //pos til en tile i world
using chunkpos = glm::ivec2; //pos til en chunk i world, heltall fra 0 - x, 0 - y

//i chunk
using cpos = glm::vec3; //pos i 3d xyz innad i chunk
using ctilepos = glm::ivec3; //tilepos i chunk
using chtilepos = glm::ivec2; //2d tilepos i chunk

using vpos = glm::vec3; //vertex pos
using vnorm = glm::vec3; //normal
using uvpos = glm::vec2; //uv pos

using point = glm::vec3; //3d point
using velocity = glm::vec3; //xyz movement speed
using rotation = glm::vec2; //horiz/vert rotation

using direction = glm::vec3; //3d direction
using hdirection = glm::vec2; //2d direction

using rgbcolor = glm::vec3; //rgb 0-1
using rgbcolor255 = glm::ivec3; //rgb 0 -255

using ytile = int; //y tile pos
using htile = int; //x,z tile pos
