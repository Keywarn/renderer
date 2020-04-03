#pragma once
#include <glm/glm.hpp>
#include "DrawingWindow.h"
#include "Colour.h"
#include "Utils.h"
#include "CanvasTriangle.h"
#include "ModelVertex.h"
#include <string>

class ModelTriangle
{
  public:
    ModelVertex vertices[3];
    glm::vec3 normal;
    Colour colour;

    ModelTriangle()
    {
    }

    ModelTriangle(ModelVertex v0, ModelVertex v1, ModelVertex v2, Colour triColour) {
      vertices[0] = v0;
      vertices[1] = v1;
      vertices[2] = v2;

      colour = triColour;
    }

    void setNormal() {
      normal = glm::cross(vertices[2].position-vertices[0].position, vertices[1].position-vertices[0].position);
    }
};

std::ostream& operator<<(std::ostream& os, const ModelTriangle& triangle)
{
    os << "(" << triangle.vertices[0].position.x << ", " << triangle.vertices[0].position.y << ", " << triangle.vertices[0].position.z << ")" << std::endl;
    os << "(" << triangle.vertices[1].position.x << ", " << triangle.vertices[1].position.y << ", " << triangle.vertices[1].position.z << ")" << std::endl;
    os << "(" << triangle.vertices[2].position.x << ", " << triangle.vertices[2].position.y << ", " << triangle.vertices[2].position.z << ")" << std::endl;
    return os;
}
