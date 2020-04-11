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

    Light()
    {
    }

    Light(glm::vec3 pos, Colour lightCol, float pow) {
      position = pos;
      colour = lightCol;
      power = pow;
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

    Colour calcDiffusePhong(RayTriangleIntersection intersect) {
      glm::vec3 r = intersect.intersectionPoint - position;
      glm::vec3 normal = interNormal(intersect);

      float val = power * std::max(glm::dot(glm::normalize(r), glm::normalize(normal)), 0.0f) / (4 * M_PI * std::pow(glm::length(r),2));

      return (Colour(val * colour.red, val * colour.blue, val * colour.green));

    }

    Colour calcSpecular(RayTriangleIntersection intersect, glm::vec3 camPos) {
      glm::vec3 viewDir = glm::normalize(camPos - intersect.intersectionPoint);
      glm::vec3 normal = interNormal(intersect);
      glm::vec3 reflectDir = glm::reflect(glm::normalize(intersect.intersectionPoint - position), normal);

      float val = std::pow(std::max(glm::dot(viewDir, reflectDir), 0.0f), 32);
      
      return (Colour(val * colour.red, val * colour.blue, val * colour.green));
    }

    glm::vec3 interNormal(RayTriangleIntersection intersect) {
      glm::vec3 n0 = intersect.intersectedTriangle.vertices[0]->normal;
      glm::vec3 n1 = intersect.intersectedTriangle.vertices[1]->normal;
      glm::vec3 n2 = intersect.intersectedTriangle.vertices[2]->normal;

      return(n0 + ((n1 - n0) * intersect.u) + ((n2 - n0) * intersect.v));
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
