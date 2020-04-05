#pragma once
#include "RayTriangleIntersection.h"
#include "ModelTriangle.h"
#include "Light.h"
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

      lookAt(glm::vec3(0,0,0));
    }

    void lookAt(glm::vec3 target) {
      glm::vec3 forward = glm::normalize(position - target);
      glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0,1,0), forward));
      glm::vec3 up = glm::normalize(glm::cross(forward, right));

      rotation[0] = right;
      rotation[1] = up;
      rotation[2] = forward;
    }

    void flat(const std::vector<ModelTriangle> tris, Light diffuseLight, Light ambientLight, DrawingWindow window) {
      float shadowBias = 0;
      bool shadows = true;
      
      //For each pixel in the image, create a ray
      for (int y = 0; y < window.height; y++) {
        for(int x = 0; x < window.width; x++){

          //Direction from the camera to the pixel in the image plane
          glm::vec3 dir = rotation * glm::normalize(position - glm::vec3(x-window.width/2, y-window.height/2, f));
          
          //Get the closest intersection of the ray
          RayTriangleIntersection closest;
          if(closestIntersection(position, dir, tris, closest, 0)) {

            //Get base colour of triangle
            Colour base = closest.intersectedTriangle.colour;
            
            //Check for object blocking direct illumination
            Colour diffuseCol = diffuseLight.calcDiffuse(closest);
            Colour ambientCol = ambientLight.calcAmbient();

            

            if(shadows) {
              RayTriangleIntersection lightBlock;
              glm::vec3 shadowStart = closest.intersectionPoint + glm::normalize(closest.intersectedTriangle.normal) * shadowBias;
              if(closestIntersection(shadowStart,glm::normalize(diffuseLight.position - closest.intersectionPoint), tris, lightBlock, 0.1f)){
                //If distance to other object is less than distance to light, in shadow
                if(glm::length(lightBlock.intersectionPoint - closest.intersectionPoint) < glm::length(diffuseLight.position - closest.intersectionPoint)){
                  diffuseCol = Colour(0,0,0);
                }
              }
            }

            Colour lit = Colour(base, ambientCol, diffuseCol);

            window.setPixelColour(window.width - x,y,lit.packed, 1/closest.distanceFromCamera);
          }
        }
      }
    }

    void gouraud(const std::vector<ModelTriangle> tris, Light diffuseLight, Light ambientLight, DrawingWindow window) {  
      float shadowBias = 0;
      bool shadows = true;    
      //For each pixel in the image, create a ray
      for (int y = 0; y < window.height; y++) {
        for(int x = 0; x < window.width; x++){

          //Direction from the camera to the pixel in the image plane
          glm::vec3 dir = rotation * glm::normalize(position - glm::vec3(x-window.width/2, y-window.height/2, f));
          
          //Get the closest intersection of the ray
          RayTriangleIntersection closest;
          if(closestIntersection(position, dir, tris, closest, 0)) {

            Colour c0 = closest.intersectedTriangle.vertColours[0];
            Colour c1 = closest.intersectedTriangle.vertColours[1];
            Colour c2 = closest.intersectedTriangle.vertColours[2];

            int red = c0.red + ((c1.red-c0.red) * closest.u) + ((c2.red-c0.red) * closest.v);
            int green = c0.green + ((c1.green-c0.green) * closest.u) + ((c2.green-c0.green) * closest.v);
            int blue = c0.blue + ((c1.blue-c0.blue) * closest.u) + ((c2.blue-c0.blue) * closest.v);

            Colour lit = Colour(red, green, blue);

            if(shadows) {
              RayTriangleIntersection lightBlock;
              glm::vec3 shadowStart = closest.intersectionPoint + glm::normalize(closest.intersectedTriangle.normal) * shadowBias;

              if(closestIntersection(shadowStart,glm::normalize(diffuseLight.position - closest.intersectionPoint), tris, lightBlock, 0.1f)){
                //If distance to other object is less than distance to light, in shadow
                if(glm::length(lightBlock.intersectionPoint - closest.intersectionPoint) < glm::length(diffuseLight.position - closest.intersectionPoint)){
                  Colour diffuseCol = Colour(0,0,0);
                  Colour ambientCol = ambientLight.calcAmbient();

                  lit = Colour(lit, diffuseCol, ambientCol);
                }
              }
            }

            window.setPixelColour(window.width - x,y,lit.packed, 1/closest.distanceFromCamera);
          }
        }
      }
    }

    std::vector<ModelTriangle> preCompGouraud(std::vector<ModelTriangle> tris, Light diffuseLight, Light ambientLight) {
      for (auto &tri : tris) {

        Colour base = tri.colour;
        Colour ambientCol = ambientLight.calcAmbient();
        for(int i = 0; i < 3; i++) {
          Colour diffuseCol = diffuseLight.calcDiffuseVertex(tri.vertices[i]);
          tri.vertColours[i] = Colour(base,ambientCol, diffuseCol);
        }
      }

      return tris;
    }


    bool closestIntersection(glm::vec3 start, glm::vec3 dir, const std::vector<ModelTriangle> tris, RayTriangleIntersection& closest, float near) {
      bool result = false;
      closest.distanceFromCamera = std::numeric_limits<float>::max();
      RayTriangleIntersection currentInter;

      for (auto &tri : tris) // access by reference to avoid copying
      { 
        if(intersectRay(tri, start, dir, currentInter)) {
          result = true;

          if(currentInter.distanceFromCamera < closest.distanceFromCamera && currentInter.distanceFromCamera > near) {
            closest = currentInter;
          }
        }
      }

      return(result);
    }

    bool intersectRay (ModelTriangle tri,glm::vec3 start, glm::vec3 dir, RayTriangleIntersection& intersect){

      glm::vec3 e1 = glm::vec3(tri.vertices[1]->position - tri.vertices[0]->position);
      glm::vec3 e2 = glm::vec3(tri.vertices[2]->position - tri.vertices[0]->position);
      glm::vec3 b = glm::vec3(start-tri.vertices[0]->position);

      glm::mat3 A( -dir, e1, e2 );
      // x = (t,u,v)
      glm::vec3 x = glm::inverse( A ) * b;

      if(x[1] > 0 && x[2] > 0 && x[1] + x[2] < 1 && x[0] >= 0) {
        intersect.distanceFromCamera = x[0];
        intersect.intersectionPoint = tri.vertices[0]->position + (e1 * x[1]) + (e2 * x[2]);
        intersect.intersectedTriangle = tri;
        intersect.u = x[1];
        intersect.v = x[2];
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
