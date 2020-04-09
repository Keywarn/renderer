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
#include <chrono>


using namespace std;
using namespace glm;

#define WIDTH 480
#define HEIGHT 395

//Camera rotations
#define PITCH glm::vec3(1,0,0)
#define YAW   glm::vec3(0,1,0)
#define ROLL   glm::vec3(0,0,1)

void draw(std::vector<ModelTriangle> tris);
void update();
void handleEvent(SDL_Event event);

DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false, 1);
Camera cam = Camera(glm::vec3(0,0,5), 200);
Model model = Model("models/cornell-box",glm::vec3(0,0,0), 1);
Model sphere = Model("models/sphere", glm::vec3(-1.8,0.9,-1.8), 1);
Model logo = Model("models/logo",glm::vec3(0,2.9,-5.4), 1.5);
Light diffuseLight = Light(glm::vec3(0, 3.8, -3), Colour(255,255,255), 50);
Light ambientLight = Light(glm::vec3(0,0,0), Colour(255,255,255), 0.5f);

int main(int argc, char* argv[])
{
  SDL_Event event;
  cam.lookAt(model.position);
  cam.position.y += 2.5;

  std::vector<ModelTriangle> tris;
  tris.reserve(sphere.tris.size() + model.tris.size() + logo.tris.size());
  tris.insert(tris.end(), model.tris.begin(), model.tris.end());
  tris.insert(tris.end(), sphere.tris.begin(), sphere.tris.end());
  tris.insert(tris.end(), logo.tris.begin(), logo.tris.end());

  tris = cam.preCompGouraud(tris, diffuseLight, ambientLight);

  std::cout.precision(5);
  while(true)
  {
    auto start = std::chrono::system_clock::now();
    // We MUST poll for events - otherwise the window will freeze !
    if(window.pollForInputEvents(&event)) handleEvent(event);
    update();
    draw(tris);
    // Need to render the frame at the end, or nothing actually gets shown on the screen !
    window.renderFrame();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> fTime = end-start;
    std::cout << "Frame Time: " << std::fixed <<fTime.count() << "s   FPS: " << std::fixed << 1/fTime.count()<< std::endl;
  }
}

void draw(std::vector<ModelTriangle> tris)
{
  window.clearPixels();
  model.display(window, cam);
  sphere.display(window, cam);
  logo.display(window, cam);
  if(window.getMode() == 3) cam.flat(tris, diffuseLight, ambientLight, window);
  else if(window.getMode() == 4) cam.gouraud(tris, diffuseLight, ambientLight, window);
}

void update()
{
  // Function for performing animation (shifting artifacts or moving the camera)
}

void handleEvent(SDL_Event event)
{
  if(event.type == SDL_KEYDOWN) {
    if(event.key.keysym.sym == SDLK_a) cam.position -= cam.rotation[0]; 
    else if(event.key.keysym.sym == SDLK_d) cam.position += cam.rotation[0];
    else if(event.key.keysym.sym == SDLK_w) cam.position -= cam.rotation[2];
    else if(event.key.keysym.sym == SDLK_s) cam.position += cam.rotation[2];
    else if(event.key.keysym.sym == SDLK_e) cam.position += cam.rotation[1];
    else if(event.key.keysym.sym == SDLK_q) cam.position -= cam.rotation[1];
    else if(event.key.keysym.sym == SDLK_l) cam.lookAt(model.position);
    else if(event.key.keysym.sym == SDLK_UP) cam.rotate(0.1, PITCH);
    else if(event.key.keysym.sym == SDLK_DOWN) cam.rotate(-0.1, PITCH);
    else if(event.key.keysym.sym == SDLK_LEFT) cam.rotate(0.1, YAW);
    else if(event.key.keysym.sym == SDLK_RIGHT) cam.rotate(-0.1, YAW);
    else if(event.key.keysym.sym == SDLK_z) cam.rotate(0.1, ROLL);
    else if(event.key.keysym.sym == SDLK_x) cam.rotate(-0.1, ROLL);
    else if(event.key.keysym.sym == SDLK_1) window.setMode(1);
    else if(event.key.keysym.sym == SDLK_2) window.setMode(2);
    else if(event.key.keysym.sym == SDLK_3) window.setMode(3);
    else if(event.key.keysym.sym == SDLK_4) window.setMode(4);
    //else if(event.key.keysym.sym == SDLK_u) CanvasTriangle(CanvasPoint(rand()%WIDTH, rand()%HEIGHT), CanvasPoint(rand()%WIDTH,rand()%HEIGHT), CanvasPoint(rand()%WIDTH, rand()%HEIGHT), Colour(rand()%WIDTH, rand()%HEIGHT, rand()%255)).outline(window);
    //else if(event.key.keysym.sym == SDLK_f) CanvasTriangle(CanvasPoint(rand()%WIDTH, rand()%HEIGHT), CanvasPoint(rand()%WIDTH,rand()%HEIGHT), CanvasPoint(rand()%WIDTH, rand()%HEIGHT), Colour(rand()%WIDTH, rand()%HEIGHT, rand()%255)).fill(window);
    else if(event.key.keysym.sym == SDLK_p) window.writeImage("export");

  }
  else if(event.type == SDL_MOUSEBUTTONDOWN) cout << "MOUSE CLICKED" << endl;
}
