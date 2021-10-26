#include "thoughpack.h"
#include <iostream>

ThoughPack::ThoughPack(double lv, double wv, double hv, std::string mat):
  Box(lv, wv, hv), material{mat}
{
  std::cout << "calling ctor of ThoughPack" <<std::endl;
}

double ThoughPack::volume() const
{
  return getLength() * getWidth() * getHeight() * 0.85;
}
