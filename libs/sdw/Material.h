#pragma once
#include <iostream>

class Material
{
  public:
    std::string name;
    Colour diffuse;
    Colour specular;
    float albedo;
    float reflect;

    float transparent;
    float ior;

    Material()
    {
      name = "";
      albedo = 1;
      specular = Colour(0,0,0);
      diffuse = Colour(0,0,0);
      reflect = 0;

      transparent = 0;
      float ior = 1;

    }

    Material(std::string mName)
    {
      name = mName;
      albedo = 1;
      specular = Colour(0,0,0);
      diffuse = Colour(0,0,0);
      reflect = 0;

      transparent = 0;
      float ior = 1;
    }

    //Simple RGB colour
    Material(Colour dif)
    {
      diffuse = dif;
      name = "";
      albedo = 1;
      specular = Colour(0,0,0);
      reflect = 0;

      transparent = 0;
      float ior = 1;
    }

    
};

std::ostream& operator<<(std::ostream& os, const Material& material)
{
    os << material.name << std::endl;
    os << "Diffuse : " << material.diffuse << std::endl;
    os << "Specular : " << material.specular << std::endl;
    return os;
}
