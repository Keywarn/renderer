#pragma once
#include "CanvasPoint.h"
#include <iostream>
#include "DrawingWindow.h"
#include "Colour.h"

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

    void display(DrawingWindow window)
    {
      float dx = to.x - from.x;
      float dy = to.y - from.y;
      float noSteps = std::max(abs(dy),abs(dx)) +1;

      float xSteps = dx/noSteps;
      float ySteps = dy/noSteps;

      float dDepth = to.depth - from.depth;
      float depthSteps = dDepth/noSteps;
      for (int i=0; i<noSteps; i++) {
        float x = from.x + xSteps*i;
        float y = from.y + ySteps*i;
        float depth = from.depth + depthSteps*i;
        window.setPixelColour(x,y,colour.packed, depth);
      }
    }


};

std::ostream& operator<<(std::ostream& os, const CanvasLine& line)
{
    os << line.from  << line.to  << line.colour << std::endl;
    return os;
}
