#ifndef RANDFUNC_H
#define RANDFUNC_H


namespace randfunc
{
    float grad(int32_t hashint, float x, float y);
    float grad(int32_t hashint, float x, float y, float z);
    inline uint8_t hashfunc(int32_t i);
    inline int32_t fastfloor(float fp);
    float noise(float x, float y, float freq);
    float noise(float x, float y, float z, float freq);

    float terrain(float wavefactor, float ampfactor, float startwave, float startamp, float ex, float ey, float ez, int levels);
    float normterrain(float wavefactor, float ampfactor, float startwave, float startamp, float ex, float ey, float ez, int levels);

    void setseed(int seed);
    int getseed();
}
#endif // RANDFUNC_H
