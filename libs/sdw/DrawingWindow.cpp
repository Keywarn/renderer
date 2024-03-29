#include "DrawingWindow.h"
#include <fstream>

// Simple constructor method
DrawingWindow::DrawingWindow()
{
}

// Complex constructor method
DrawingWindow::DrawingWindow(int w, int h, bool fullscreen, int m, bool a, bool s)
{
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) !=0) {
    printMessageAndQuit("Could not initialise SDL: ", SDL_GetError());
  }

  width = w;
  height = h;
  //MODE: 1 wireframe, 2 rasterise, 3 raytrace
  mode = m;
  AA = a;
  SS = s;
  pixelBuffer = new uint32_t[width*height];
  depthBuffer = new float[width*height];
  std::fill_n(depthBuffer, width*height, 0);
  clearPixels();

  uint32_t flags = SDL_WINDOW_OPENGL;
  if(fullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
  int ANYWHERE = SDL_WINDOWPOS_UNDEFINED;
  window = SDL_CreateWindow("Renderer", ANYWHERE, ANYWHERE, width, height, flags);
  if(window == 0) printMessageAndQuit("Could not set video mode: ", SDL_GetError());

  flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  renderer = SDL_CreateRenderer(window, -1, flags);
  if(renderer == 0) printMessageAndQuit("Could not create renderer: ", SDL_GetError());

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_RenderSetLogicalSize(renderer, width, height);

  int PIXELFORMAT = SDL_PIXELFORMAT_ARGB8888;
  texture = SDL_CreateTexture(renderer, PIXELFORMAT, SDL_TEXTUREACCESS_STATIC, width, height);
  if(texture == 0) printMessageAndQuit("Could not allocate texture: ", SDL_GetError());
}

// Deconstructor method
void DrawingWindow::destroy()
{
  delete[] pixelBuffer;
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void DrawingWindow::renderFrame()
{
  SDL_UpdateTexture(texture, NULL, pixelBuffer, width*sizeof(uint32_t));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

bool DrawingWindow::pollForInputEvents(SDL_Event *event)
{
  if(SDL_PollEvent(event)) {
    if((event->type == SDL_QUIT) || ((event->type == SDL_KEYDOWN) && (event->key.keysym.sym == SDLK_ESCAPE))) {
      destroy();
      printMessageAndQuit("Exiting", NULL);
    }
    return true;
  }
  return false;
}

void DrawingWindow::setPixelColour(int x, int y, uint32_t colour, float depth)
{
  if((x<0) || (x>=width) || (y<0) || (y>=height)) {
    
  }
  else {
    if(depth > getDepth(x,y))
    {
      pixelBuffer[(y*width)+x] = colour;
      depthBuffer[(y*width)+x] = depth;
    }
  }
}

uint32_t DrawingWindow::getPixelColour(int x, int y)
{
  if((x<0) || (x>=width) || (y<0) || (y>=height)) {
    std::cout << x << "," <<  y << " not on visible screen area" << std::endl;
    return -1;
  }
  else return pixelBuffer[(y*width)+x];
}

float DrawingWindow::getDepth(int x, int y)
{
  if((x<0) || (x>=width) || (y<0) || (y>=height)) {
    std::cout << x << "," <<  y << " not on visible screen area" << std::endl;
    return -1;
  }
  else return depthBuffer[(y*width)+x];
}

void DrawingWindow::clearPixels()
{
  memset(pixelBuffer, 0, width * height * sizeof(uint32_t));
  memset(depthBuffer, 0, width * height * sizeof(float));
}

void DrawingWindow::setMode(int m) {
    if(m == 1)      std::cout << "WIREFRAME MODE" << std::endl;
    else if(m == 2) std::cout << "RASTERISE MODE" << std::endl;
    else if(m == 3) std::cout << "RAYTRACE (FLAT) MODE" << std::endl;
    else if(m == 4) std::cout << "RAYTRACE (GOURAUD) MODE" << std::endl;
    else if(m == 5) std::cout << "RAYTRACE (PHONG) MODE" << std::endl;
    mode = m;
  }


int DrawingWindow::getMode() {
  return(mode);
}

void DrawingWindow::antiAliasing(bool a){
  if(a == true){
    AA = false;
    std::cout << "Anti-Aliasing Off" << std::endl;
  }
  if(a == false){
    AA = true;
    std::cout << "Anti-Aliasing On" << std::endl;
  }
}

bool DrawingWindow::getAA(){
  return AA;
}

void DrawingWindow::superSampling(bool s){
  if(s == true){
    SS = false;
    std::cout << "Super Samping Off" << std::endl;
  }
  if(s == false){
    SS = true;
    std::cout << "Super Samping On" << std::endl;
  }
}

bool DrawingWindow::getSS(){
  return SS;
}

void DrawingWindow::writeImage(std::string fname) {
  std::ofstream img;
  img.open(fname + ".ppm", std::ios::binary);
  img << "P6\n";
  img << width << ' ' << height << '\n';
  img << "255\n";

  for (int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++){
          uint32_t col = getPixelColour(x,y);
          uint8_t r = (col >> 16) & 255;
          uint8_t g = (col >> 8) & 255;
          uint8_t b = col & 255;
          img << r << g << b;
        }
      }

  img.close();
}
