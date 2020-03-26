#include <Image.h>
#include <CanvasLine.h>
#include <ModelTriangle.h>
#include <CanvasTriangle.h>
#include <DrawingWindow.h>
#include <Model.h>
#include <Utils.h>
#include <Light.h>
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

DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false, 1);
Camera cam = Camera(glm::vec3(0,0,5), 200);
Model model = Model("cornell-box",glm::vec3(0,0,0), 1);
Light diffuseLight = Light(glm::vec3(0, 3.8, -3), Colour(255,255,255), 50);
Light ambientLight = Light(glm::vec3(0,0,0), Colour(255,255,255), 5);

int main(int argc, char* argv[])
{
  SDL_Event event;
  cam.lookAt(model.position);

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
  window.clearPixels();
  model.display(window, cam);
  if(window.getMode() == 3) {
    std::cout << "New Frame" <<std::endl;
    cam.raytrace(model.tris, diffuseLight, ambientLight, window);
  }
}

void update()
{
  cam.lookAt(model.position);
  // Function for performing animation (shifting artifacts or moving the camera)
}

void handleEvent(SDL_Event event)
{
  if(event.type == SDL_KEYDOWN) {
    if(event.key.keysym.sym == SDLK_LEFT) cam.position.x -= 1; 
    else if(event.key.keysym.sym == SDLK_RIGHT) cam.position.x += 1;
    else if(event.key.keysym.sym == SDLK_UP) cam.position.y += 1;
    else if(event.key.keysym.sym == SDLK_DOWN) cam.position.y -= 1;
    else if(event.key.keysym.sym == SDLK_1) window.setMode(1);
    else if(event.key.keysym.sym == SDLK_2) window.setMode(2);
    else if(event.key.keysym.sym == SDLK_3) window.setMode(3);
    //else if(event.key.keysym.sym == SDLK_u) CanvasTriangle(CanvasPoint(rand()%WIDTH, rand()%HEIGHT), CanvasPoint(rand()%WIDTH,rand()%HEIGHT), CanvasPoint(rand()%WIDTH, rand()%HEIGHT), Colour(rand()%WIDTH, rand()%HEIGHT, rand()%255)).outline(window);
    //else if(event.key.keysym.sym == SDLK_f) CanvasTriangle(CanvasPoint(rand()%WIDTH, rand()%HEIGHT), CanvasPoint(rand()%WIDTH,rand()%HEIGHT), CanvasPoint(rand()%WIDTH, rand()%HEIGHT), Colour(rand()%WIDTH, rand()%HEIGHT, rand()%255)).fill(window);
    else if(event.key.keysym.sym == SDLK_e) window.writeImage("test");

  }
  else if(event.type == SDL_MOUSEBUTTONDOWN) cout << "MOUSE CLICKED" << endl;
}
