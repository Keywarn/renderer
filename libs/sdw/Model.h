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
    std::vector<ModelVertex > vertices;
    std::vector<glm::vec2 > texPoints;
    std::vector<ModelTriangle> tris;
    std::unordered_map<std::string, Colour> mats;
    float scale;
    glm::vec3 position;

    bool textured;
    Image texture;

    Model(){
      scale = 1;
      textured = false;
    }

    Model(std::string mName,glm::vec3 pos, float sf){
      
      scale = sf;
      position = pos;

      std::ifstream matFile;
      matFile.open(mName + ".mtl", std::ios::binary);

      std::string str;

      textured = false;

      //Read in the materials file
      while (getline(matFile, str)) {
        std::string* toks = split(str, ' ');
        if (toks[0] == "newmtl") {
          std::string matName = toks[1];
          getline(matFile, str);
          toks = split(str, ' ');
          //If it is a plain colour
          if(toks[0] == "Kd") {
            mats[matName] = Colour(std::stof(toks[1])*255, std::stof(toks[2])*255, std::stof(toks[3])*255);
          }
          //If it has a texture
          else if(toks[0] == "map_Kd") {
            //Set default colour to grey for non-textured modes
            mats[matName] = Colour(75,75,75);
            textured = true;
            texture = Image("models/" + toks[1]);
          }
        }
      }
      //Sweep for vertices
      std::ifstream vertFile;
      vertFile.open(mName + ".obj", std::ios::binary);

      while (getline(vertFile, str)) {
        std::string* toks = split(str, ' ');
        if (toks[0] == "v") {
          vertices.push_back(ModelVertex(glm::vec3(std::stof(toks[1]),std::stof(toks[2]),std::stof(toks[3])) + position));
        }
        if (toks[0] == "vt") {
          texPoints.push_back(glm::vec2(std::stof(toks[1]),std::stof(toks[2])));
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
          if(textured) {
            tri.textured = true;
            tri.texture = &texture;
          }

          for (int i = 0; i < 3; i++) {
            std::string* index = split(toks[i+1], '/');
            tri.vertices[i] = &vertices[std::stoi(index[0])-1];
            if(textured) tri.texPoints[i] = texPoints[std::stoi(index[1])-1];
          }
          tri.colour = curColour;
          tri.setNormal();

          for (int i = 0; i < 3; i++) {
            tri.vertices[i]->normal += tri.normal;
          }

          for (int i = 0; i < vertices.size(); i++) {
            glm::normalize(vertices[i].normal);
          }
          tris.push_back(tri);
        } 
      }
    }

    void display(DrawingWindow window, Camera cam) {
      for (auto &tri : tris) // access by reference to avoid copying
      {  
        CanvasTriangle canTri;
        canTri.colour = tri.colour;

        for(int i = 0; i < 3; i++){
          glm::vec3 camToP = ((tri.vertices[i]->position) - cam.position) * cam.rotation;
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
    }
};

std::ostream& operator<<(std::ostream& os, const Model& model)
{
    os << "Material Map: " << std::endl;
    outHash(model.mats);
    return os;
}
