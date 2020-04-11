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
      glm::vec3 normal = interNormal(intersect.intersectedTriangle.vertices[0]->normal, intersect.intersectedTriangle.vertices[1]->normal, intersect.intersectedTriangle.vertices[2]->normal, intersect.u, intersect.v);

      float val = power * std::max(glm::dot(glm::normalize(r), glm::normalize(normal)), 0.0f) / (4 * M_PI * std::pow(glm::length(r),2));

      return (Colour(val * colour.red, val * colour.blue, val * colour.green));

    }

    Colour calcSpecular(RayTriangleIntersection intersect, glm::vec3 camPos) {
      glm::vec3 viewDir = glm::normalize(camPos - intersect.intersectionPoint);
      glm::vec3 normal = interNormal(intersect.intersectedTriangle.vertices[0]->normal, intersect.intersectedTriangle.vertices[1]->normal, intersect.intersectedTriangle.vertices[2]->normal, intersect.u, intersect.v);
      glm::vec3 reflectDir = glm::reflect(glm::normalize(intersect.intersectionPoint - position), glm::normalize(normal));

      float val = std::pow(std::max(glm::dot(viewDir, reflectDir), 0.0f), 10);
      
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
