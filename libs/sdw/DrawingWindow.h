#pragma once
#include "SDL.h"
#include <iostream>
#include <algorithm>

class DrawingWindow
{

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  uint32_t *pixelBuffer;
  float *depthBuffer;
  int mode;
  int AA;
  int SS;

public:
  int height;
  int width;

  // Constructor method
  DrawingWindow();
  DrawingWindow(int w, int h, bool fullscreen, int m, bool a, bool s);
  void destroy();
  void renderFrame();
  bool pollForInputEvents(SDL_Event *event);
  void setPixelColour(int x, int y, uint32_t colour, float depth);
  uint32_t getPixelColour(int x, int y);
  float getDepth(int x, int y);
  void clearPixels();
  void writeImage(std::string fname);

  void printMessageAndQuit(const char* message, const char* error)
  {
    if(error == NULL) {
      std::cout << message << std::endl;
      exit(0);
    }
    else {
      std::cout << message << " " << error <<std::endl;
      exit(1);
    }
  }

  void setMode(int m);

  int getMode();

  void antiAliasing(bool a);
  bool getAA();

  void superSampling(bool s);
  bool getSS();

};
