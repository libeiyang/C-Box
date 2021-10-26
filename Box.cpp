#include <iostream>
#include <sstream>
#include "Box.h"

// Constructor definition
Box::Box(double lv, double wv, double hv)
    : length{lv}, width{wv}, height{hv}
{
  std::cout << "Box constructor 1 called with parameters " << length << ", " << width << ", " << height << std::endl;
}

// Constructor for Box that is a cube
Box::Box(double side) : Box{side, side, side}
{
  std::cout << "Box constructor 2 called." << std::endl;
}

Box::Box(const Box & other): length{other.length}, width{other.width}, height{other.height}, content{other.content}
{
  std::cout << "Making of copy of an existing box" << std::endl;
}

// Function to calculate the volume of a box
double Box::volume() const
{
  return length*width*height;
}

const std::string &Box::getContent() const
{
  return content;
}

void Box::setContent(const std::string &newContent)
{
  content = newContent;
}

void Box::fillBox(std::string_view content)
{
  setContent(std::string{content});
}

std::string Box::showBox() const
{
  std::stringstream res;
  res << "box volume = " << volume() << std::endl;
  res << "with content : " << getContent() << std::endl;
  return res.str();

}

bool Box::operator< (const Box & other) const
{
  return volume() < other.volume();
}

bool Box::operator< (double otherVolume)
{
  return volume() < otherVolume;
}


bool Box::operator==(const Box &other) const
{
  return volume() == other.volume();
}

Box Box::operator+(const Box &b) const
{
  Box temp{*this};
  temp += b;
//  Box temp{std::max(length, b.length), std::max(width, b.width), height+b.height};
//  temp.fillBox(content + " and " + b.content);
  return temp;
}

Box &Box::operator+=(const Box &b)
{
  length = std::max(length, b.length);
  width = std::max(width, b.width);
  height += b.height;
  content += " and " + b.content;
  return *this;
}


Box &Box::operator++()
{
  content += " + extra gift";
  return *this;
}

Box Box::operator++(int)
{
  Box temp{*this};
  //  content += "extra gift";
  ++(*this);
  return temp;
}




bool operator<(double otherVolume, const Box & b)
{
  return otherVolume < b.volume();
}

std::ostream & operator<<(std::ostream & os, const Box & b)
{
  os << b.showBox();
  return os;
}
