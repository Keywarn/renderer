#pragma once
#include <glm/glm.hpp>
#include "Colour.h"
#include "RayTriangleIntersection.h"

class Light
{
  public:
    glm::vec3 position;
    Colour colour;
    float power;

    Light()
    {
    }

    Light(glm::vec3 pos, Colour lightCol, float pow) {
      position = pos;
      colour = lightCol;
      power = pow;
    }

    Colour calcLight(const RayTriangleIntersection intersect)  {
      return Colour();
    }  
};

std::ostream& operator<<(std::ostream& os, const Light& light)
{
    os << "Position (" << light.position.x << ", " << light.position.y << ", " << light.position.z << ")" << std::endl;
    os << "Colour   (" << light.colour.red << ", " << light.colour.green << ", " << light.colour.blue << ")" << std::endl;
    os << "Power    (" << light.power << ")" << std::endl;
    return os;
}
