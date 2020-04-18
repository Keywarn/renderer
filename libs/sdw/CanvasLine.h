#pragma once
#include "CanvasPoint.h"
#include <iostream>
#include "DrawingWindow.h"
#include "Colour.h"
#include <vector>
#include <glm/glm.hpp>

class CanvasLine
{
  public:
    CanvasPoint from;
    CanvasPoint to;
    Colour colour;

    CanvasLine()
    {
    }

    CanvasLine(CanvasPoint v0, CanvasPoint v1)
    {
      from = v0;
      to = v1;
      colour = Colour(255,255,255);
    }

    CanvasLine(CanvasPoint v0, CanvasPoint v1, Colour c)
    {
      from = v0;
      to = v1;
      colour = c;
    }

    std::vector <float> interpolate(float from, float to, float numberOfValues)
    {
      std::vector <float> interpolateVector(numberOfValues);
      float difference = (to-from)/(numberOfValues-1);
      for(int i = 0;i<numberOfValues;i++){
        interpolateVector[i] = from + (i * difference);
      }
      return interpolateVector;
    }
    
    
    std::vector <glm::vec3> interpolate3(glm::vec3 from, glm::vec3 to, int numberOfValues)
    {
      std::vector <glm::vec3> interpolateVector(numberOfValues);
      float difference1 = (to[0]-from[0])/(numberOfValues-1);
      float difference2 = (to[1]-from[1])/(numberOfValues-1);
      float difference3 = (to[2]-from[2])/(numberOfValues-1);
      for(int i = 0;i<numberOfValues;i++){
        interpolateVector[i][0] = from[0] + (i * difference1);
        interpolateVector[i][1] = from[1] + (i * difference2);
        interpolateVector[i][2] = from[2] + (i * difference3);
      }
      return interpolateVector;
    }
    
    void setPixel(float horizontal , float vertical, int index, Colour colour, DrawingWindow window, double depth){
      
      int previousRed = (window.getPixelColour(horizontal, vertical) >> 16) & 0xFF;
      int previousGreen = (window.getPixelColour(horizontal, vertical) >> 8) & 0xFF;
      int previousBlue = (window.getPixelColour(horizontal, vertical)) & 0xFF; 
      std::vector<glm::vec3> range = interpolate3({colour.red, colour.green, colour.blue}, {previousRed, previousGreen, previousBlue}, 11);
      uint32_t colouring = (255<<24) + (int(range[index][0])<<16) + (int(range[index][1])<<8) + int(range[index][2]);
      
      //uint32_t colouring = (255<<24) + (int(144)<<16) + (int(144)<<8) + int(144);
      window.setPixelColour(horizontal, vertical, colouring, depth);  
    }

    void display(DrawingWindow window) 
    {
      //float dx = abs(from.x - to.x);
      //float dy = abs(from.y - to.y);
      //float noSteps = std::max(dx, dy) + 1;
      
      float dx = to.x - from.x;
      float dy = to.y - from.y;
      float noSteps = std::max(abs(dy),abs(dx)) +1;

      float xSteps = dx/noSteps;
      float ySteps = dy/noSteps;

    
      float depthSteps = (to.depth - from.depth)/noSteps;

      //std::vector<float> horizontal = interpolate(from.x, to.x, noSteps);
      //std::vector<float> vertical = interpolate(from.y, to.y, noSteps);

      for (int i=0; i<noSteps; i++) {
        //float x = horizontal[i];
        //float y = vertical[i];
        float x = from.x + xSteps*i;
        float y = from.y + ySteps*i;
        float depth = from.depth + depthSteps*i;
        
        if(window.getAA() == true){
          bool bHorizontal;
          float horizontalValue, verticalValue, fractional;
          if(dy >= dx){
              fractional = (modf(x + 0.5, &horizontalValue));
              verticalValue = y;
              bHorizontal = true;
          }
          if(dy < dx){
              fractional = (modf(y + 0.5, &verticalValue));
              horizontalValue = x;
              bHorizontal = false;
          }
          if(fractional == 0.5){
              window.setPixelColour(horizontalValue, verticalValue, colour.packed, depth);
          }  
          if(fractional < 0.5){
              float percentage = fractional + 0.5;
              int index;
              if((int(percentage*100) % 10) > 5){
                  index = 10 - ((int(percentage*10)  % 10) + 1);
              }
              else {index = 10 - (int(percentage*10)  % 10);} 
              setPixel(horizontalValue, verticalValue, index, colour, window, depth);
  
              percentage = 0.5 - fractional;
              if((int(percentage*100) % 10) > 5){
                  index = 10 - ((int(percentage*10)  % 10) + 1);
              }
              else {index = 10 - (int(percentage*10)  % 10);}
              if(bHorizontal){setPixel(horizontalValue - 1, verticalValue, index, colour, window, depth);}
              else{setPixel(horizontalValue, verticalValue-1, index, colour, window, depth);}
          }
          if(fractional > 0.5){
              float percentage = (0.5 + (1 - fractional));
              int index;
              if((int(percentage*100) % 10) > 5){
                  index = 10 - ((int(percentage*10)  % 10) + 1);
              }
              else {index = 10 - (int(percentage*10)  % 10);}
              setPixel(horizontalValue, verticalValue, index, colour, window, depth);
              percentage = (1 - (0.5 + (1 - fractional)));
              if((int(percentage*100) % 10) > 5){
                  index = 10 - ((int(percentage*10)  % 10) + 1);
              }
              else {index = 10 - (int(percentage*10)  % 10);}
              if(bHorizontal){setPixel(horizontalValue + 1, verticalValue, index, colour, window, depth);}
              else{setPixel(horizontalValue, verticalValue+1, index, colour, window, depth);}
          }
        }
        if(window.getAA() == false){
          window.setPixelColour(x,y,colour.packed, depth);
        }
      }
    }


};

std::ostream& operator<<(std::ostream& os, const CanvasLine& line)
{
    os << line.from  << line.to  << line.colour << std::endl;
    return os;
}
