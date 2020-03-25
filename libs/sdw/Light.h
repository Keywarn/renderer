#pragma once
#include <glm/glm.hpp>
#include "Colour.h"

class Light
{
  public:
    glm::vec3 position;
    Colour colour;
    float power;

    Light()
    {
    }

    Light(glm::vec3 pos, Colour ligthCol, float pow) {
      position = pos;
      colour = lightCol;
      power = pow;
    }    
};

std::ostream& operator<<(std::ostream& os, const Light& light)
{
    os << "Position (" << light.position[0].x << ", " << light.position[0].y << ", " << light.position[0].z << ")" << std::endl;
    os << "Colour   (" << light.colour.r << ", " << light.colour.g << ", " << light.colour.b << ")" << std::endl;
    os << "Power    (" << light.power << ")" << std::endl;
    return os;
}
