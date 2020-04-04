#pragma once
#include "ModelTriangle.h"
#include <glm/glm.hpp>
#include <iostream>

class RayTriangleIntersection
{
  public:
    glm::vec3 intersectionPoint;
    float distanceFromCamera;
    ModelTriangle intersectedTriangle;
    float u;
    float v;

    RayTriangleIntersection() {
        
    }

    RayTriangleIntersection(glm::vec3 point, float distance, ModelTriangle tri, float uu, float vv)
    {
        intersectionPoint = point;
        distanceFromCamera = distance;
        intersectedTriangle = tri;
        u = uu;
        v = vv;
    }
};

// std::ostream& operator<<(std::ostream& os, const RayTriangleIntersection& intersection)
// {
//     os << "Intersection is at " << intersection.intersectionPoint << " on triangle " << intersection.intersectedTriangle << " at a distance of " << intersection.distanceFromCamera << std::endl;
//     return os;
// }
