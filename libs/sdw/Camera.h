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

    void raytrace(const std::vector<ModelTriangle> tris, DrawingWindow window) {
      
      for (int y = 0; y < window.height; y++) {
        for(int x = 0; x < window.width; x++){

          glm::vec3 dir = rotation * glm::normalize(glm::vec3(x-window.width/2, y-window.height/2, -f));
          
          RayTriangleIntersection closest;
          if(closestIntersection(position, dir, tris, closest)) {
            std::cout<<"pixel"<<std::endl;
            window.setPixelColour(x,window.height-y,closest.intersectedTriangle.colour.packed, 1/closest.distanceFromCamera);
          }
        }
      }
    }


    bool closestIntersection(glm::vec3 start, glm::vec3 dir, const std::vector<ModelTriangle> tris, RayTriangleIntersection& closest) {
      bool result = false;
      closest.distanceFromCamera = std::numeric_limits<float>::max();
      RayTriangleIntersection currentInter;

      for (auto &tri : tris) // access by reference to avoid copying
      { 
        if(intersectRay(tri, start, dir, currentInter)) {
          result = true;

          if(currentInter.distanceFromCamera < closest.distanceFromCamera) {
            closest = currentInter;
          }
        }
      }

      return(result);
    }

    bool intersectRay (ModelTriangle tri,glm::vec3 start, glm::vec3 dir, RayTriangleIntersection& intersect){

      glm::vec3 e1 = glm::vec3(tri.vertices[1] - tri.vertices[0]);
      glm::vec3 e2 = glm::vec3(tri.vertices[2] - tri.vertices[0]);
      glm::vec3 b = glm::vec3(start-tri.vertices[0]);

      glm::mat3 A( -dir, e1, e2 );
      // x = (t,u,v)
      glm::vec3 x = glm::inverse( A ) * b;

      if(x[1] > 0 && x[2] > 0 && x[1] + x[2] < 1 && x[0] >= 0) {
        intersect.distanceFromCamera = x[0];
        intersect.intersectionPoint = tri.vertices[0] + (e1 * x[1]) + (e2 * x[2]);
        intersect.intersectedTriangle = tri;
        return true;
      }
      else {
        return (false);
      }
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
