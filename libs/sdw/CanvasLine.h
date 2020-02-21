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
      float noSteps = std::max(abs(dy),abs(dx));

      float xSteps = dx/noSteps;
      float ySteps = dy/noSteps;
      for (int i=0; i<noSteps; i++) {
        float x = from.x + xSteps*i;
        float y = from.y + ySteps*i;
        window.setPixelColour(x,y,colour.packed);
      }
    }


};

std::ostream& operator<<(std::ostream& os, const CanvasLine& line)
{
    os << line.from  << line.to  << line.colour << std::endl;
    return os;
}
