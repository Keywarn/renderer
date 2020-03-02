#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <DrawingWindow.h>
#include <Colour.h>

class Image
{
  public:
    int width;
    int height;
    int maxVal;
    std::vector< std::vector< Colour > > data;

    Image()
    {
    }

    Image(std::string fName)
    {
      std::ifstream file;
      file.open(fName, std::ios::binary);
      std::vector<std::string> header;
      std::string line;

      for(int i =0; i < 3; i++) {

        std::getline(file,line);

        if(line.at(0) != '#'){
          header.push_back(line);
        }
        else{
          i--;
        }

      }

      std::stringstream ss(header[1]);
      std::string widthStr, heightStr;

      std::getline(ss, widthStr, ' ');
      std::getline(ss, heightStr, ' ');

      width = std::stoi(widthStr);
      height = std::stoi(heightStr);

      maxVal = std::stoi(header[2]);

      for (int y = 0; y < height; y++) {
        std::vector< Colour > row;
        
        for(int x = 0; x < width; x++){
          Colour col = Colour(file.get(),file.get(),file.get());
          row.push_back(col);
        }

        data.push_back(row);
      }
    }

    void display(DrawingWindow window)
    {
      for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
          window.setPixelColour(x,y,data[y][x].packed, 1);
        }
      }
    }
};

std::ostream& operator<<(std::ostream& os, const Image& image)
{
    os << "width: " << image.width << ", height: " << image.height << ", maxVal: " << image.maxVal << std::endl;
    return os;
}
