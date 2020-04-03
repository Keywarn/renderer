#pragma once
#include <glm/glm.hpp>
#include "Colour.h"
#include "Utils.h"
#include <string>

class ModelVertex
{
  public:
    glm::vec3 position;
    glm::vec3 normal;
    Colour colour;

    ModelVertex()
    {
    }

    ModelVertex(glm::vec3 pos, Colour col) {
      position = pos;
      
      colour = col;
      normal = glm::vec3(0,0,0);
    }
};