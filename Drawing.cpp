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

#define WIDTH 640
#define HEIGHT 480

//Camera rotations
#define PITCH glm::vec3(1,0,0)
#define YAW   glm::vec3(0,1,0)
#define ROLL   glm::vec3(0,0,1)

//Camera sampling patterns
#define NO_AA       {glm::vec2(0.5,0.5)}
#define TWOBYTWO    {glm::vec2(0.25,0.25),glm::vec2(0.75,0.25),glm::vec2(0.25,0.75),glm::vec2(0.755,0.75)}
#define RGSS        {glm::vec2(0.625,0.125),glm::vec2(0.125,0.375),glm::vec2(0.875,0.625),glm::vec2(0.375,0.875)}
#define FOURBYFOUR  {glm::vec2(0.125,0.125),glm::vec2(0.375,0.125),glm::vec2(0.625,0.125),glm::vec2(0.875,0.125),glm::vec2(0.125,0.375),glm::vec2(0.375,0.375),glm::vec2(0.625,0.375),glm::vec2(0.875,0.375),glm::vec2(0.125,0.625),glm::vec2(0.375,0.625),glm::vec2(0.625,0.625),glm::vec2(0.875,0.625),glm::vec2(0.125,0.875),glm::vec2(0.375,0.875),glm::vec2(0.625,0.875),glm::vec2(0.875,0.875)}

//Parameters to change sampling in scene
//Samples for global illumination of diffuse surfaces
//Anti-aliasing samples
//Cells in light (per dimension)
#define DIF_SAMPLES 1
#define AA_MODE     NO_AA
#define CELLS       1

void draw(std::vector<ModelTriangle> tris);
void update();
void handleEvent(SDL_Event event);

DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false, 1, false, false);
Camera cam = Camera(glm::vec3(0,0,5), 200, AA_MODE, 5);
Model model = Model("models/cornell-box",glm::vec3(0,0,0), 1);
Model sphere = Model("models/sphere", glm::vec3(-1.8,0.9,-1.8), 1);
Model logo = Model("models/logo",glm::vec3(0,2.9,-5.4), 1.5);
Light diffuseLight = Light(glm::vec3(-0.884011, 5.118497, -3.567968), Colour(255,255,255), 60, glm::vec3(1.3, 0,0), glm::vec3(0,0,1.05),CELLS,CELLS);
Light ambientLight = Light(glm::vec3(0,0,0), Colour(255,255,255), 0.25f);

std::vector<Light> dLights = {diffuseLight};

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
    if(window.getMode() > 2) window.writeImage("export");
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> fTime = end-start;
    if(window.getMode() > 2) std::cout << "Frame Time: " << std::fixed <<fTime.count() << "s   FPS: " << std::fixed << 1/fTime.count()<< std::endl;
  }
}

void draw(std::vector<ModelTriangle> tris)
{
  window.clearPixels();
  if (window.getMode() == 1 || window.getMode() == 2){
    model.display(window, cam);
    sphere.display(window, cam);
    logo.display(window, cam);
  }
  else if(window.getMode() == 3) cam.flat(tris, diffuseLight, ambientLight, window);
  else if(window.getMode() == 4) cam.gouraud(tris, diffuseLight, ambientLight, window);
  else if(window.getMode() == 5) cam.phong(tris, dLights, DIF_SAMPLES, window);
}

void update()
{
  // Function for performing animation (shifting artifacts or moving the camera)
}

void handleEvent(SDL_Event event)
{
  if(event.type == SDL_KEYDOWN) {
    if(event.key.keysym.sym == SDLK_a) cam.move(-cam.rotation[0]); 
    else if(event.key.keysym.sym == SDLK_d) cam.move(cam.rotation[0]);
    else if(event.key.keysym.sym == SDLK_w) cam.move(-cam.rotation[2]);
    else if(event.key.keysym.sym == SDLK_s) cam.move(cam.rotation[2]);
    else if(event.key.keysym.sym == SDLK_e) cam.move(cam.rotation[1]);
    else if(event.key.keysym.sym == SDLK_q) cam.move(-cam.rotation[1]);
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
    else if(event.key.keysym.sym == SDLK_5) window.setMode(5);
    //else if(event.key.keysym.sym == SDLK_u) CanvasTriangle(CanvasPoint(rand()%WIDTH, rand()%HEIGHT), CanvasPoint(rand()%WIDTH,rand()%HEIGHT), CanvasPoint(rand()%WIDTH, rand()%HEIGHT), Colour(rand()%WIDTH, rand()%HEIGHT, rand()%255)).outline(window);
    //else if(event.key.keysym.sym == SDLK_f) CanvasTriangle(CanvasPoint(rand()%WIDTH, rand()%HEIGHT), CanvasPoint(rand()%WIDTH,rand()%HEIGHT), CanvasPoint(rand()%WIDTH, rand()%HEIGHT), Colour(rand()%WIDTH, rand()%HEIGHT, rand()%255)).fill(window);
    else if(event.key.keysym.sym == SDLK_p) window.writeImage("export");
    else if(event.key.keysym.sym == SDLK_j) window.antiAliasing(window.getAA());
    else if(event.key.keysym.sym == SDLK_k) window.superSampling(window.getSS());

  }
  else if(event.type == SDL_MOUSEBUTTONDOWN) cout << "MOUSE CLICKED" << endl;
}
