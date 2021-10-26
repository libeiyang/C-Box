#include <iostream>
#include <memory>
#include <vector>
#include "Box.h"
#include "truckload.h"
#include "thoughpack.h"
#include "boost/core/demangle.hpp"

int main()
{
  Box box1 {2.0, 3.0, 4.0};           // An arbitrary box
  Box box2 {5.0};                     // A box that is a cube
  std::cout << "box1 volume = " << box1.volume() << std::endl;
  std::cout << "with content : " << box1.getContent() << std::endl;
  box1.fillBox("C++ books");
  box2.fillBox("bottles");
  std::cout << box1 << "and some extra info" << std::endl;
  auto box3 = std::make_shared<Box>(4.0, 5.0, 6.0);
  std::cout << "box2 volume = " << box3->volume() << std::endl;
  Box * box31 = new Box(3.0);
  std::cout << box31->volume() << std::endl;
  Box boxes[4];
  for (Box & b: boxes)
    std::cout << "box2 volume = " << b.volume() << std::endl;
  std::vector<Box> boxCollection;
  boxCollection.reserve(2);
  boxCollection.push_back(box1);
  boxCollection.push_back(boxes[2]);
  for (Box & b: boxCollection)
    std::cout << "box2 volume = " << b.volume() << std::endl;
  std::vector<std::shared_ptr<Box>> boxPtrCollection;
  boxPtrCollection.push_back(box3);
  for (auto & b: boxPtrCollection)
    std::cout << "box2 volume = " << b->volume() << std::endl;
  //  showBox(6.0);
  std::cout << "Loading the truck" << std::endl;
  TruckLoad truck;
  auto truckBox = std::make_unique<Box>(1.5);
  truckBox->fillBox("books");
  truckBox->showBox();
  truck.addBox(std::move(truckBox));
  truck.largestBox()->showBox();
  auto tp1 = std::make_unique<ThoughPack>(1.0, 2.0, 2.5, "plastic");
  tp1->fillBox("bottles");
  ThoughPack test;
  std::cout << "volume of test " << test.volume() << std::endl;
  truck.addBox(std::move(tp1));
  truck.largestBox()->showBox();
  if (box1 < box2)
    {
      std::cout << "box1 " << box1 << " is smaller than box2 " << box2 << std::endl;
    }
  if (box1 < 30.0) // box1.operator<(30.0);
    {
      std::cout << "box1 is a small box" << std::endl;
    }
  if (30.0 < box2)
    {
      std::cout << "box2 is a big box" << std::endl;
    }
  //once you have < and ==, compiler can deduce the other relational operators
  std::cout << std::boolalpha << (box1 == box2) << std::endl;
  std::cout << std::boolalpha << (box2 >= box2) << std::endl;
  std::cout << std::boolalpha << (box2 > box1) << std::endl;
  Box bigBox = box1 + box2;
  std::cout << bigBox;
  bigBox += box1 += box2;
  std::cout << box1 << bigBox;
  //increment, prefix and postfix
  ++box2;
  std::cout << box2;
  Box testop = box1++;
  std::cout << testop << std::endl;
  std::cout << box1 << std::endl;
  //overloading []
  std::cout << *(truck[0]);
  //overloaded [] for const objects -> first need to define copy ctor of TruckLoad
  //default version will make copy of each attribute -> will not work here due to unique_ptrs
  const TruckLoad ct{truck};
  std::cout << "const version : " << *(ct[0]);
  //special case, idea is to return content of TruckLoad at that position
  //look also to implementation in std::vector; stl_vector.h l 1042
  truck[1]->setContent("bottles of champagne");
  std::cout << *(truck[1]);
  try {
    {
      std::cout << *(truck[5]);
    }
  }  catch (std::exception & e)
  {
    std::cout << e.what() << std::endl;
  }
  //is the largest box a ThoughPack?
  auto & largest = truck.largestBox();
  //use RTTI or casting
  std::cout << "largest box is a " << typeid(*largest).name() << std::endl;
  std::cout << "demangled name = " << boost::core::demangle(typeid(*largest).name()) << std::endl;
  //cast on raw pointer (.get()) for shared ptrs std::dynamic_pointer_cast()
  if (dynamic_cast<ThoughPack *>(largest.get())) //returns nullptr if not a TP
      std::cout << "largest box is of type ThoughPack" << std::endl;
  else
      std::cout << "largest box is of type Box" << std::endl;
  //alternative
  try
  {
    dynamic_cast<ThoughPack&>(*largest);
  }
  catch (std::bad_cast & e)
  {
    std::cout << "Certainly not a ThoughPack ! " << e.what() << std::endl;
  }
//  /*other casts
//  static_cast<new type>(var) == like in C (new type)
//  const_cast<type without const>(const type) -> try to avoid
//  reinterpret_cast<same bit pattern in other type>(var) ->for low level stuff
  truck.sortLoad();
  std::cout << "after sorting " << *(truck[0]);
  truck.sortLoad(SmallerSurface());
  std::cout << "after sorting by surface " << *(truck[0]);
  std::cout << std::boolalpha << "Possible to put all boxes in the truck " << truck.checkLoad() << std::endl;

}
