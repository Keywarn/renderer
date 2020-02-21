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

    Colour(int r, int g, int b)
    {
      name = "";
      red = r;
      green = g;
      blue = b;

      packed = (255<<24) + (red<<16) + (green<<8) + blue;
    }

    Colour(std::string n, int r, int g, int b)
    {
      name = n;
      red = r;
      green = g;
      blue = b;

      packed = (255<<24) + (red<<16) + (green<<8) + blue;
    }
};

std::ostream& operator<<(std::ostream& os, const Colour& colour)
{
    os << colour.name << " [" << colour.red << ", " << colour.green << ", " << colour.blue << "]";
    return os;
}
