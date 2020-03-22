#pragma once
#include <glm/glm.hpp>
#include "DrawingWindow.h"
#include "Colour.h"
#include "Utils.h"
#include "Camera.h"
#include "CanvasTriangle.h"
#include <string>

class ModelTriangle
{
  public:
    glm::vec3 vertices[3];
    Colour colour;

    ModelTriangle()
    {
    }

    ModelTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, Colour trigColour)
    {
      vertices[0] = v0;
      vertices[1] = v1;
      vertices[2] = v2;
      colour = trigColour;
    }

    void display(DrawingWindow window, Camera cam, float scale, glm::vec3 position) {
      CanvasTriangle canTri;
      canTri.colour = colour;

      for(int i = 0; i < 3; i++){
        glm::vec3 camToP = ((vertices[i] + position) - cam.position) * cam.rotation;
        camToP.x = scale * cam.f * camToP.x / camToP.z;
        camToP.y = scale * cam.f * camToP.y / camToP.z;
        CanvasPoint canP = CanvasPoint(- camToP.x + window.width/2,camToP.y + window.height/2, -1/camToP.z);
        canTri.vertices[i] = canP;
      }
      if(window.getMode() == 1) {
        canTri.outline(window);
      }
      else if(window.getMode() == 2) {
        canTri.fill(window);
      }
      else if(window.getMode() == 3) {
        //RAYTRACE BABY
      }
    }
};

std::ostream& operator<<(std::ostream& os, const ModelTriangle& triangle)
{
    os << "(" << triangle.vertices[0].x << ", " << triangle.vertices[0].y << ", " << triangle.vertices[0].z << ")" << std::endl;
    os << "(" << triangle.vertices[1].x << ", " << triangle.vertices[1].y << ", " << triangle.vertices[1].z << ")" << std::endl;
    os << "(" << triangle.vertices[2].x << ", " << triangle.vertices[2].y << ", " << triangle.vertices[2].z << ")" << std::endl;
    return os;
}
