#ifndef CAMERA_H
#define CAMERA_H

#include "windowmanager.h"
#include "settings.h"

namespace camera
{
    void updateviewmatrix(wposition pos, rotation rot);
    void updateperspective();
    glm::mat4& getviewmatrix();
    glm::mat4& getperspective();
    glm::mat4& getpvmatrix();
};

#endif // CAMERA_H
