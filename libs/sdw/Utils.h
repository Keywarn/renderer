#pragma once
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <TexturePoint.h>
#include <CanvasPoint.h>

std::string* split(std::string line, char delim);

std::string* split(std::string line, char delim)
{
    int numberOfTokens = count(line.begin(), line.end(), delim) + 1;
    std::string *tokens = new std::string[numberOfTokens];
    int currentPosition = 0;
    int nextIndex = 0;
    for(int i=0; i<numberOfTokens ;i++) {
        nextIndex = line.find(delim, currentPosition);
        tokens[i] = line.substr(currentPosition,nextIndex-currentPosition);
        currentPosition = nextIndex + 1;
    }
    return tokens;
}

std::vector<float> inter(float from, float to, float numberOfValues){

  float step = (to-from) / (numberOfValues-1);
  std::vector<float> inter;

  for (int i = 0; i < numberOfValues; i++){
    inter.push_back(from + step * i);
  }
  return inter;
}

std::vector<glm::vec2> inter2D(glm::vec2 from, glm::vec2 to, int numberOfValues){

  std::vector<glm::vec2> inter;
  glm::vec2 step = (to - from) / float(std::max(numberOfValues-1,1));
  glm::vec2 cur = from;
  
  for (int i = 0; i < numberOfValues; i++){
    inter.push_back(cur);
    cur += step;
  }
  return inter;
}

std::vector<TexturePoint> inter2DTex(TexturePoint from, TexturePoint to, float numberOfValues){

  std::vector<TexturePoint> inter;
  glm::vec2 step;
  step.x = (to.x-from.x) / (numberOfValues-1);
  step.y = (to.y-from.y) / (numberOfValues-1);
  
  for (int i = 0; i < numberOfValues; i++){
    TexturePoint point;
    point.x = from.x + step.x * i;
    point.y = from.y + step.y * i;
    inter.push_back(point);
  }
  return inter;
}

std::vector<glm::vec3> inter3D(glm::vec3 from, glm::vec3 to, float numberOfValues){

  std::vector<glm::vec3> inter;
  glm::vec3 step;
  step.x = (to.x-from.x) / (numberOfValues-1);
  step.y = (to.y-from.y) / (numberOfValues-1);
  step.z = (to.z-from.z) / (numberOfValues-1);
  
  
  for (int i = 0; i < numberOfValues; i++){
    glm::vec3 vec;
    vec.x = from.x + step.x * i;
    vec.y = from.y + step.y * i;
    vec.z = from.z + step.z * i;

    inter.push_back(vec);
  }
  return inter;
}

float pointDist(CanvasPoint a, CanvasPoint b)
{
  return pow(pow(a.y-b.y,2) + pow(a.x-b.x,2),0.5f);
}

float pointDist(TexturePoint a, TexturePoint b)
{
  return pow(pow(a.y-b.y,2) + pow(a.x-b.x,2),0.5f);
}

template<typename K, typename V>
void outHash(std::unordered_map<K,V> const &m){
  for (auto it = m.cbegin(); it != m.cend(); ++it) {
        std::cout << "{" << (*it).first << ": " << (*it).second << "}" << std::endl;
      }
}

template<typename T>
void outVec(std::vector<T> const &v){
  for (auto i = v.begin(); i != v.end(); ++i)
    std::cout << *i << std::endl;
}