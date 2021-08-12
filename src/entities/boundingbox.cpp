#include "consts.h"
#include "boundingbox.h"

boundingbox::boundingbox(box fbbox)
{
    bbox = fbbox;
}

boundingbox::boundingbox() = default;

boundingbox::~boundingbox()
{
    //dtor
}

void boundingbox::changeboundingbox(box fbbox)
{
    bbox = fbbox;
}

boundingbox::box& boundingbox::getbox()
{
    return bbox;
}

bool boundingbox::collisionwith(box fbbox)
{
    if (glm::any(glm::lessThan(bbox.points[1], fbbox.points[0])) || glm::any(glm::greaterThan(bbox.points[0], fbbox.points[1]))) return false;

    /*
    if(bbox.point[1].x < fbbox.point[0].x || bbox.point[0].x > fbbox.point[1].x) return false;
    if(bbox.point[1].y < fbbox.point[0].y || bbox.point[0].y > fbbox.point[1].y) return false;
    if(bbox.point[1].z < fbbox.point[0].z || bbox.point[0].z > fbbox.point[1].z) return false;
    */

    return true;
}
