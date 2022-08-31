#ifndef RENDERER_H
#define RENDERER_H

#include "chunkcontroller.h"
#include "maincharcontroller.h"
#include "shadercontroller.h"
#include "inputmanager.h"
#include "environment.h"
#include "texturemanager.h"
#include "uicontroller.h"
#include "uiingame.h"

namespace renderer
{
    void rendergame();
    glm::vec4& getmousedata();
    void updaterenderfilter();
};

#endif // RENDERER_H
