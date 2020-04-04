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

    ModelVertex()
    {
    }

    ModelVertex(glm::vec3 pos) {
      position = pos;
      normal = glm::vec3(0,0,0);
    }
};