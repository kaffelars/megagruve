#include "consts.h"
#include "camera.h"

namespace camera
{
    glm::mat4 viewmatrix;
    glm::mat4 projection;

    glm::mat4 pvmatrix;
}

void camera::updateviewmatrix(wposition pos, rotation rot)
{
    viewmatrix = glm::lookAt
    (
        glm::vec3(0,0,0),
        glm::vec3(0,0,4),
        glm::vec3(0,-1,0)
    );

    float kex = ((float)rot.x*pi_value/180)/3;
    float key = ((float)rot.y*pi_value/180)/3;
    viewmatrix = glm::rotate(viewmatrix, key, glm::vec3(1, 0, 0));
    viewmatrix = glm::rotate(viewmatrix, -kex, glm::vec3(0, 1, 0));

    viewmatrix = glm::translate(viewmatrix, -pos);

    pvmatrix = projection * viewmatrix;
}

void camera::updateperspective()
{
    projection = glm::perspective
    (
        settings::getfov(),
        windowmanager::windowaspectratio(),
        1.0f,
        1000.0f
    );

    pvmatrix = projection * viewmatrix;
}

glm::mat4& camera::getviewmatrix()
{
    return viewmatrix;
}

glm::mat4& camera::getperspective()
{
    return projection;
}

glm::mat4& camera::getpvmatrix()
{
    return pvmatrix;
}
