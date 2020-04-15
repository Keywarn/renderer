#pragma once
#include <glm/glm.hpp>
#include <math.h>
#include "Colour.h"
#include "RayTriangleIntersection.h"

class Light
{
  public:
    glm::vec3 position;
    Colour colour;
    float power;

    //Area light properties
    glm::vec3 uVec;
    glm::vec3 vVec;
    int uSteps;
    int vSteps;

    Light()
    {
    }

    Light(glm::vec3 pos, Colour lightCol, float pow) {
      position = pos;
      colour = lightCol;
      power = pow;

      uVec = glm::vec3(1,0,0);
      vVec = glm::vec3(0,0,1);
      uSteps = 1;
      vSteps = 1;
    }

    Light(glm::vec3 pos, Colour lightCol, float pow, glm::vec3 uV, glm::vec3 vV, int uS, int vS) {
      position = pos;
      colour = lightCol;
      power = pow;

      uVec = uV;
      vVec = vV;
      uSteps = uS;
      vSteps = vS;
    }

    Colour calcDiffuse(RayTriangleIntersection intersect)  {
      glm::vec3 r = intersect.intersectionPoint - position;
      
      float val = power * std::max(glm::dot(glm::normalize(r), glm::normalize(intersect.intersectedTriangle.normal)), 0.0f) / (4 * M_PI * std::pow(glm::length(r),2));
      
      return (Colour(val * colour.red, val * colour.blue, val * colour.green));
    }

    Colour calcDiffuseVertex(ModelVertex* vertex)  {
      glm::vec3 r = vertex->position - position;
      
      float val = power * std::max(glm::dot(glm::normalize(r), glm::normalize(vertex->normal)), 0.0f) / (4 * M_PI * std::pow(glm::length(r),2));
      
      return (Colour(val * colour.red, val * colour.blue, val * colour.green));
    }

    Colour calcAmbient() {
      return (Colour(power * colour.red, power * colour.blue, power * colour.green));
    }
};

std::ostream& operator<<(std::ostream& os, const Light& light)
{
    os << "Position (" << light.position.x << ", " << light.position.y << ", " << light.position.z << ")" << std::endl;
    os << "Colour   (" << light.colour.red << ", " << light.colour.green << ", " << light.colour.blue << ")" << std::endl;
    os << "Power    (" << light.power << ")" << std::endl;
    return os;
}
