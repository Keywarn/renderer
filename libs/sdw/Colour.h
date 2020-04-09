#pragma once
#include <iostream>

class Colour
{
  public:
    std::string name;
    int red;
    int green;
    int blue;
    uint32_t packed;

    Colour()
    {
    }

    //Simple RGB colour
    Colour(int r, int g, int b)
    {
      name = "";
      red = r;
      green = g;
      blue = b;

      packed = (255<<24) + (red<<16) + (green<<8) + blue;
    }

    //Colour from base, diffuse and amibent pass
    Colour(Colour base, Colour ambient, Colour diffuse) {
      red = base.red * (ambient.red + diffuse.red)/255;
      green = base.green * (ambient.green + diffuse.green)/255;
      blue = base.blue * (ambient.blue + diffuse.blue)/255;

      fix();
      packed = packed = (255<<24) + (red<<16) + (green<<8) + blue;
    }

    Colour(std::string n, int r, int g, int b)
    {
      name = n;
      red = r;
      green = g;
      blue = b;
      
      packed = (255<<24) + (red<<16) + (green<<8) + blue;
    }

    void fix(){
      red = std::max(std::min(red, 255), 0);
      green = std::max(std::min(green, 255), 0);
      blue = std::max(std::min(blue, 255), 0);

      packed = (255<<24) + (red<<16) + (green<<8) + blue;
    }

    Colour operator+ (Colour param) {
      return Colour(red + param.red, green + param.green, blue + param.blue);
    }
};

std::ostream& operator<<(std::ostream& os, const Colour& colour)
{
    os << colour.name << " [" << colour.red << ", " << colour.green << ", " << colour.blue << "]";
    return os;
}
