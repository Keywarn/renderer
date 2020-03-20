#pragma once
#include <string>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "DrawingWindow.h"
#include "Colour.h"
#include "Utils.h"
#include "Camera.h"

class Model
{
  public:
    std::vector<glm::vec3 > vertices;
    std::vector<ModelTriangle> tris;
    std::unordered_map<std::string, Colour> mats;
    float scale;
    glm::vec3 position;

    Model(){
      scale = 1;
    }

    Model(std::string mName,glm::vec3 pos, float sf){
      
      scale = sf;
      position = pos;

      std::ifstream matFile;
      matFile.open(mName + ".mtl", std::ios::binary);

      std::string str;

      //Read in the materials file
      while (getline(matFile, str)) {
        std::string* toks = split(str, ' ');
        if (toks[0] == "newmtl") {
          std::string matName = toks[1];
          getline(matFile, str);
          toks = split(str, ' ');
          mats[matName] = Colour(std::stof(toks[1])*255, std::stof(toks[2])*255, std::stof(toks[3])*255);
        }
      }
      //Sweep for vertices
      std::ifstream vertFile;
      vertFile.open(mName + ".obj", std::ios::binary);

      while (getline(vertFile, str)) {
        std::string* toks = split(str, ' ');
        if (toks[0] == "v") {
          vertices.push_back(glm::vec3(std::stof(toks[1]),std::stof(toks[2]),std::stof(toks[3])));
        }
      }

      //Sweep for faces and material assignments
      std::ifstream triFile;
      triFile.open(mName + ".obj", std::ios::binary);
      
      Colour curColour;
      while (getline(triFile, str)) {
        
        std::string* toks = split(str, ' ');
        if (toks[0] == "usemtl") {
          curColour = mats[toks[1]];
        }

        if (toks[0] == "f") {
          ModelTriangle tri;

          for (int i = 0; i < 3; i++) {
            std::string* index = split(toks[i+1], '/');
            tri.vertices[i] = vertices[std::stoi(index[0])-1];
          }

          tri.colour = curColour;
          tris.push_back(tri);
        } 
      }
    }

    void wireframe(DrawingWindow window, Camera cam) {
      for (auto &tri : tris) // access by reference to avoid copying
      {  
        CanvasTriangle canTri;
        canTri.colour = tri.colour;

        for(int i = 0; i < 3; i++){
          glm::vec3 camToP = (tri.vertices[i] + position) - cam.position;
          camToP.x = scale * cam.f * camToP.x / camToP.z;
          camToP.y = scale * cam.f * camToP.y / camToP.z;
          CanvasPoint canP = CanvasPoint(camToP.x + window.width/2,camToP.y + window.height/2, -1/camToP.z);
          canTri.vertices[i] = canP;
        }
        canTri.outline(window);
      }
    }

    void display(DrawingWindow window, Camera cam, bool wf) {
      for (auto &tri : tris) // access by reference to avoid copying
      {  
        CanvasTriangle canTri;
        canTri.colour = tri.colour;

        for(int i = 0; i < 3; i++){
          glm::vec3 camToP = cam.rotation * ((tri.vertices[i] + position) - cam.position);
          camToP.x = scale * cam.f * camToP.x / camToP.z;
          camToP.y = scale * cam.f * camToP.y / camToP.z;
          CanvasPoint canP = CanvasPoint(camToP.x + window.width/2,camToP.y + window.height/2, -1/camToP.z);
          canTri.vertices[i] = canP;
        }
        canTri.fill(window);
        if(wf) {
          canTri.colour = Colour(255,255,255);
          canTri.outline(window);
        }
      }
    }

};

std::ostream& operator<<(std::ostream& os, const Model& model)
{
    os << "Material Map: " << std::endl;
    outHash(model.mats);
    os << "Face Data: " << std::endl;
    outVec(model.tris);
    return os;
}
