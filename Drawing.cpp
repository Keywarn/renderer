#include <Image.h>
#include <CanvasLine.h>
#include <ModelTriangle.h>
#include <CanvasTriangle.h>
#include <DrawingWindow.h>
#include <Model.h>
#include <Utils.h>
#include <glm/glm.hpp>
#include <fstream>
#include <vector>


using namespace std;
using namespace glm;

#define WIDTH 480
#define HEIGHT 395

void draw();
void update();
void handleEvent(SDL_Event event);

DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);

int main(int argc, char* argv[])
{
  SDL_Event event;
  Model model = Model("cornell-box", 1);
  Camera cam = Camera(glm::vec3(0,3,5), 200);
  model.display(window, cam, false);

  while(true)
  {
    // We MUST poll for events - otherwise the window will freeze !
    if(window.pollForInputEvents(&event)) handleEvent(event);
    update();
    draw();
    // Need to render the frame at the end, or nothing actually gets shown on the screen !
    window.renderFrame();
  }
}

void draw()
{
  //window.clearPixels();
}

void update()
{
  // Function for performing animation (shifting artifacts or moving the camera)
}

void handleEvent(SDL_Event event)
{
  if(event.type == SDL_KEYDOWN) {
    if(event.key.keysym.sym == SDLK_LEFT) cout << "LEFT" << endl;
    else if(event.key.keysym.sym == SDLK_RIGHT) cout << "RIGHT" << endl;
    else if(event.key.keysym.sym == SDLK_UP) cout << "UP" << endl;
    else if(event.key.keysym.sym == SDLK_DOWN) cout << "DOWN" << endl;
    else if(event.key.keysym.sym == SDLK_u) CanvasTriangle(CanvasPoint(rand()%WIDTH, rand()%HEIGHT), CanvasPoint(rand()%WIDTH,rand()%HEIGHT), CanvasPoint(rand()%WIDTH, rand()%HEIGHT), Colour(rand()%WIDTH, rand()%HEIGHT, rand()%255)).outline(window);
    else if(event.key.keysym.sym == SDLK_f) CanvasTriangle(CanvasPoint(rand()%WIDTH, rand()%HEIGHT), CanvasPoint(rand()%WIDTH,rand()%HEIGHT), CanvasPoint(rand()%WIDTH, rand()%HEIGHT), Colour(rand()%WIDTH, rand()%HEIGHT, rand()%255)).fill(window);

  }
  else if(event.type == SDL_MOUSEBUTTONDOWN) cout << "MOUSE CLICKED" << endl;
}
