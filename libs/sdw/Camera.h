#pragma once
#include "RayTriangleIntersection.h"
#include "ModelTriangle.h"
#include <glm/glm.hpp>
#include <string>
#include <limits>

class Camera
{
  public:
    glm::vec3 position;
    glm::mat3 rotation;
    float f;

    Camera()
    {
    }

    Camera(glm::vec3 pos, float foc){
      position = pos;
      rotation = glm::mat3();
      f = foc;
    }

    void lookAt(glm::vec3 target) {
      glm::vec3 forward = glm::normalize(position - target);
      glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0,1,0), forward));
      glm::vec3 up = glm::normalize(glm::cross(forward, right));

      rotation[0] = right;
      rotation[1] = up;
      rotation[2] = forward;
    }

    bool closestIntersection(glm::vec3 start, glm::vec3 dir, const std::vector<ModelTriangle> tris, RayTriangleIntersection& closest) {
      bool result = false;
      closest.distanceFromCamera = std::numeric_limits<float>::max();
      RayTriangleIntersection currentInter;

      for (auto &tri : tris) // access by reference to avoid copying
      { 
        glm::vec3 start;
        glm::vec3 dir;

        if(tri.intersectRay(start, dir, currentInter)) {
          result = true;

          if(currentInter.distanceFromCamera < closest.distanceFromCamera) {
            closest = currentInter;
          }
        }
      }

      return(result);
    }
};

std::ostream& operator<<(std::ostream& os, const Camera& camera)
{
    os << "Camera Position: " << "[" << camera.position.x << "," << camera.position.y << "," << camera.position.z << "]"<< std::endl;
    os << "Camera Rotation: " << "|" << camera.rotation[0].x << "," << camera.rotation[1].x << "," << camera.rotation[2].x << "|"<< std::endl;
          os << "                 |" << camera.rotation[0].y << "," << camera.rotation[1].y << "," << camera.rotation[2].y << "|"<< std::endl;
          os << "                 |" << camera.rotation[0].z << "," << camera.rotation[1].z << "," << camera.rotation[2].z << "|"<< std::endl;
    os << "Camera Focal Length: " << camera.f;
    return os;
}
