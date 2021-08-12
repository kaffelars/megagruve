#ifndef FRAMEBUFFERCONTROLLER_H
#define FRAMEBUFFERCONTROLLER_H

#include "vaocontainer.h"
#include "settings.h"
#include "scenequad.h"

namespace framebuffercontroller
{
    void initialize();
    void resizebuffers();
    void setupbuffers();

    void activatebuffertextures();
    void activatepostprocessingtextures();

    void deactivatebuffertextures();

    void copydepthbuffer();

    void cleanup();
    void close();

    extern GLuint tilebuffer, tilepos, tilergb, tilenorm, gTexture, gLight, tiledepth, postdepth, postbuffer, postrgb;

    void blur();
};

#endif // FRAMEBUFFERCONTROLLER_H
