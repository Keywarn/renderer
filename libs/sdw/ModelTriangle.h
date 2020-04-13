#pragma once
#include <glm/glm.hpp>
#include "DrawingWindow.h"
#include "Colour.h"
#include "Utils.h"
#include "CanvasTriangle.h"
#include "ModelVertex.h"
#include "Material.h"
#include <string>

class ModelTriangle
{
  public:
    ModelVertex* vertices[3];
    glm::vec3 normal;
    Material material;
    Colour vertColours[3];

    bool textured;
    Image* texture;
    glm::vec2 texPoints[3];

    bool bumped;
    Image* bump;
    float nm;

    ModelTriangle() {
      textured = false;
      bumped = false;
    }

    ModelTriangle(ModelVertex* v0, ModelVertex* v1, ModelVertex* v2, Material mat){
      vertices[0] = v0;
      vertices[1] = v1;
      vertices[2] = v2;

      textured = false;
      bumped = false;

      material = mat;
    }

    ModelTriangle(ModelVertex* v0, ModelVertex* v1, ModelVertex* v2, Image* tex, glm::vec2 tP0, glm::vec2 tP1, glm::vec2 tP2, Material mat){
      vertices[0] = v0;
      vertices[1] = v1;
      vertices[2] = v2;

      textured = true;
      bumped = false;
      texture = tex;

      texPoints[0] = tP0;
      texPoints[1] = tP1;
      texPoints[2] = tP2;

      material = mat;
    }

    void setNormal() {
      normal = glm::cross(vertices[2]->position-vertices[0]->position, vertices[1]->position-vertices[0]->position);
    }
};

std::ostream& operator<<(std::ostream& os, const ModelTriangle& triangle)
{
    os << "(" << triangle.vertices[0]->position.x << ", " << triangle.vertices[0]->position.y << ", " << triangle.vertices[0]->position.z << ")" << std::endl;
    os << "(" << triangle.vertices[1]->position.x << ", " << triangle.vertices[1]->position.y << ", " << triangle.vertices[1]->position.z << ")" << std::endl;
    os << "(" << triangle.vertices[2]->position.x << ", " << triangle.vertices[2]->position.y << ", " << triangle.vertices[2]->position.z << ")" << std::endl;
    return os;
}
