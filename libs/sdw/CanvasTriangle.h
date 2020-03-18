#pragma once
#include "CanvasPoint.h"
#include "DrawingWindow.h"
#include "Image.h"
#include <iostream>
#include "Utils.h"

class CanvasTriangle
{

  public:
    CanvasPoint vertices[3];
    Colour colour;
    Image texture;

    CanvasTriangle()
    {
    }

    CanvasTriangle(CanvasPoint v0, CanvasPoint v1, CanvasPoint v2)
    {
      vertices[0] = v0;
      vertices[1] = v1;
      vertices[2] = v2;
      colour = Colour(255,255,255);
    }

    CanvasTriangle(CanvasPoint v0, CanvasPoint v1, CanvasPoint v2, Colour c)
    {
      vertices[0] = v0;
      vertices[1] = v1;
      vertices[2] = v2;
      colour = c;
    }
    CanvasTriangle(CanvasPoint v0, CanvasPoint v1, CanvasPoint v2, Image t)
    {
      vertices[0] = v0;
      vertices[1] = v1;
      vertices[2] = v2;
      colour = Colour(255,255,255);
      texture = t;
    }

    void outline(DrawingWindow window)
    {
      CanvasLine(vertices[0], vertices[1], colour).display(window);
      CanvasLine(vertices[1], vertices[2], colour).display(window);
      CanvasLine(vertices[2], vertices[0], colour).display(window);
    }

    void  order()
    {
      if(vertices[1].y < vertices[0].y) std::swap(vertices[1], vertices[0]);
      if(vertices[2].y < vertices[1].y) std::swap(vertices[2], vertices[1]);
      if(vertices[1].y < vertices[0].y) std::swap(vertices[1], vertices[0]);
    }
    
    CanvasPoint getMid()
    {
      return CanvasPoint(vertices[0].x + ((vertices[1].y - vertices[0].y) / (vertices[2].y - vertices[0].y)) * (vertices[2].x - vertices[0].x), vertices[1].y, vertices[0].depth + ((vertices[1].y - vertices[0].y) / (vertices[2].y - vertices[0].y)) * (vertices[2].depth - vertices[0].depth));
    }

    

    void fill(DrawingWindow window)
    {
      order();
      int rows = vertices[2].y-vertices[0].y + 1;
      std::vector<int> leftPixels(rows);
      std::vector<int> rightPixels(rows);

      for( int i = 0; i < rows; ++i ) {
        leftPixels[i] = +std::numeric_limits<int>::max();
        rightPixels[i] = -std::numeric_limits<int>::max();
      }

      for( int i = 0; i < 3; i++) {
        int occRows = std::abs(vertices[i].y-vertices[(i+1)%3].y + 1);
        std::vector<glm::vec2> points = inter2D(glm::vec2 (vertices[i].x, vertices[i].y), glm::vec2 (vertices[(i+1)%3].x,vertices[(i+1)%3].y), occRows + 1);
        for(int j = 0; j < occRows; j++) {
          int rowsIndex = points[j].y - vertices[0].y;
          
          if(leftPixels[rowsIndex] > points[j].x) {
            leftPixels[rowsIndex] = points[j].x;
          }

          if(rightPixels[rowsIndex] < points[j].x) {
            rightPixels[rowsIndex] = points[j].x;
          }
        }
      }

      for( int i = 0; i < rows; ++i ) {
        CanvasLine(CanvasPoint(leftPixels[i], vertices[0].y + i), CanvasPoint(rightPixels[i], vertices[0].y + i), colour).display(window);
      }
    }

    void texTopTri(DrawingWindow window)
    {
      if (vertices[1].x > vertices[2].x) {
        std::swap(vertices[1], vertices[2]);
      }

      float gradLeft = (vertices[1].x - vertices[0].x) / (vertices[1].y - vertices[0].y);
      float gradRight = (vertices[2].x - vertices[0].x) / (vertices[2].y - vertices[0].y);

      float xLeft = vertices[0].x;
      float xRight = vertices[0].x;

      for (int fillY = vertices[0].y; fillY <= vertices[1].y; fillY++)
      {
        float texLineSize = xRight-xLeft + 1;

        float leftFrac = pointDist(vertices[0], CanvasPoint(xLeft, fillY)) / pointDist(vertices[0], vertices[1]);
        TexturePoint texLeft = TexturePoint(vertices[0].texturePoint.x + (vertices[1].texturePoint.x - vertices[0].texturePoint.x) * leftFrac, vertices[0].texturePoint.y + (vertices[1].texturePoint.y - vertices[0].texturePoint.y) * leftFrac);
     
        float rightFrac = pointDist(vertices[0], CanvasPoint(xRight, fillY)) / pointDist(vertices[0], vertices[2]);
        TexturePoint texRight = TexturePoint(vertices[0].texturePoint.x + (vertices[2].texturePoint.x - vertices[0].texturePoint.x) * rightFrac, vertices[0].texturePoint.y + (vertices[2].texturePoint.y - vertices[0].texturePoint.y) * rightFrac);

        std::vector< TexturePoint> vals = inter2DTex(texLeft, texRight, texLineSize);

        for (int fillX = std::round(xLeft); fillX <= std::round(xRight); fillX++)
        {
          window.setPixelColour(fillX,fillY,texture.data[std::round(vals[fillX-xLeft].y)][std::round(vals[fillX-xLeft].x)].packed, 2);
        }

        xLeft += gradLeft;
        xRight += gradRight;
      }
    }

    void texBotTri(DrawingWindow window)
    {
      if (vertices[0].x > vertices[1].x) {
        std::swap(vertices[0], vertices[1]);
      }

      float gradLeft = (vertices[2].x - vertices[0].x) / (vertices[2].y - vertices[0].y);
      float gradRight = (vertices[2].x - vertices[1].x) / (vertices[2].y - vertices[1].y);

      float xLeft = vertices[2].x;
      float xRight = vertices[2].x;

      for (int fillY = vertices[2].y; fillY > vertices[0].y; fillY--)
      {
        float texLineSize = xRight-xLeft + 1;

        float leftFrac = pointDist(vertices[2], CanvasPoint(xLeft, fillY)) / pointDist(vertices[2], vertices[0]);
        TexturePoint texLeft = TexturePoint(vertices[2].texturePoint.x + (vertices[0].texturePoint.x - vertices[2].texturePoint.x) * leftFrac, vertices[2].texturePoint.y + (vertices[0].texturePoint.y - vertices[2].texturePoint.y) * leftFrac);
     
        float rightFrac = pointDist(vertices[2], CanvasPoint(xRight, fillY)) / pointDist(vertices[2], vertices[1]);
        TexturePoint texRight = TexturePoint(vertices[2].texturePoint.x + (vertices[1].texturePoint.x - vertices[2].texturePoint.x) * rightFrac, vertices[2].texturePoint.y + (vertices[1].texturePoint.y - vertices[2].texturePoint.y) * rightFrac);

        std::vector< TexturePoint> vals = inter2DTex(texLeft, texRight, texLineSize);

        for (int fillX = std::round(xLeft); fillX <= std::round(xRight); fillX++)
        {
          window.setPixelColour(fillX,fillY,texture.data[std::round(vals[fillX-xLeft].y)][std::round(vals[fillX-xLeft].x)].packed, 2);
        }

        xLeft -= gradLeft;
        xRight -= gradRight;
      }
    }

    void texFill(DrawingWindow window) {
      order();
      CanvasPoint mid = getMid();

      float midFrac = pointDist(vertices[0], mid) / pointDist(vertices[0], vertices[2]);

      mid.texturePoint = TexturePoint(vertices[0].texturePoint.x + (vertices[2].texturePoint.x - vertices[0].texturePoint.x) * midFrac, vertices[0].texturePoint.y + (vertices[2].texturePoint.y - vertices[0].texturePoint.y) * midFrac);
  
      CanvasTriangle(vertices[0], mid, vertices[1], texture).texTopTri(window);
      CanvasTriangle(vertices[1], mid, vertices[2], texture).texBotTri(window);
  

      outline(window);
    }
    
};

std::ostream& operator<<(std::ostream& os, const CanvasTriangle& triangle)
{
    os << triangle.vertices[0]  << triangle.vertices[1]  << triangle.vertices[2];
    return os;
}
