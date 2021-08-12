#ifndef LINEDRAWER_H
#define LINEDRAWER_H

#include "utils.h"
#include "shadercontroller.h"
#include "windowmanager.h"
#include "vaocontainer.h"

namespace linedrawer
{
    void render(cameracontroller& camera);

    void clearlines();

    void addline(glm::vec3 start, glm::vec3 slutt, float rgb);

    void compile();

    void initialize();

    void drawrect(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float rgb);
};

#endif // LINEDRAWER_H
