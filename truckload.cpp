#include "truckload.h"
#include "Box.h"
#include <stdexcept>

TruckLoad::TruckLoad(float maxDim): maxDimension{maxDim}
{

}

TruckLoad::TruckLoad(const TruckLoad &other)
{
  if (&other != this)
    {
//    maxDimension = other.maxDimension;
    for (auto & b : other.load)
      {
        addBox(std::make_unique<Box>(*b));
      }
    }
}

void TruckLoad::addBox(std::unique_ptr<Box> box)
{
  load.push_back(std::move(box));
}

const std::unique_ptr<Box> & TruckLoad::largestBox() const
{
  unsigned int largest{0};
  for (unsigned int index = 1; index < load.size(); index++)
    {
      if (load[index]->volume() > load[largest]->volume())
        {
          largest = index;
        }
    }
  return load[largest];
}

std::unique_ptr<Box> & TruckLoad::operator [](unsigned int index)
{
  if (index >= load.size())
    throw std::out_of_range("invalid index");
  return load.at(index);
}

const std::unique_ptr<Box> &TruckLoad::operator [](unsigned int index) const
{
  if (index >= load.size())
    throw std::out_of_range("invalid index");
  return load.at(index);
}

void TruckLoad::sortLoad()
{
//  std::sort(load.begin(), load.end(), SmallerVolume());
  std::sort(load.begin(), load.end(),
            [](auto & b1, auto & b2)
  {return b1->volume() < b2->volume();});
}

void TruckLoad::sortLoad(std::function<bool (const std::unique_ptr<Box> &, const std::unique_ptr<Box> &)> compBox)
{
  std::sort(load.begin(), load.end(), compBox);
}

//can all boxes pass through the door?
bool TruckLoad::checkLoad()
{
  auto res = std::find_if(load.begin(), load.end(), [&](auto & b)
  {return (b->getWidth() > maxDimension) && (b->getLength() > maxDimension) &&
    (b->getHeight() > maxDimension);});
  return res == load.end();
}
