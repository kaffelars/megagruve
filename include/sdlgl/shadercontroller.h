#ifndef SHADERCONTROLLER_H
#define SHADERCONTROLLER_H

#include "shader.h"

namespace shadercontroller
{
    void initialize();
    void activateshader(int shadernum);
    GLuint getuniformid(std::string uniformname);

    enum eshaders
    {
        SH_MAIN, SH_SCENE, SH_SKY, SH_PP, SH_LINE, SH_ICONS, SH_WATER, SH_BOB
    };
}


#endif // SHADERCONTROLLER_H
