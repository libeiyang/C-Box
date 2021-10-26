#ifndef BOX_H
#define BOX_H
#include <string>
#include <memory>

#include <utility>

using namespace std::rel_ops;

class Box
{
public:
  // Constructors
  Box(double lv, double wv, double hv);
  explicit Box(double side); // Constructor for a cube
  Box() =default;
  Box(const Box & other);
  virtual double volume() const;                                  // Function to calculate the volume of a box

  const std::string &getContent() const;
  void setContent(const std::string &newContent);

  void fillBox(std::string_view content);
  std::string showBox() const;
  double getLength()  const {return length;};

  double getWidth() const {return width;} ;

  double getHeight() const {return height;};
  bool operator< (const Box & other) const;
  bool operator< (double otherVolume);

  bool operator==(const Box & other) const;

  Box operator+(const Box & b) const;
  Box & operator+=(const Box & b);
  Box & operator++(); //prefix
  Box operator++(int); //postfix


private:
  double length {1.0};
  double width {1.0};
  double height {1.0};
  std::string content{"empty"};
};

bool operator<(double otherVolume, const Box & b);
std::ostream & operator<<(std::ostream & os, const Box & b);

//function objects
class SmallerVolume
{
public:
  bool operator()(const std::unique_ptr<Box> & b1, const std::unique_ptr<Box> & b2)
  {
    return b1->volume() < b2->volume();
  }
};

//height of boxes is not important
class SmallerSurface
{
public:
  bool operator()(const std::unique_ptr<Box> & b1, const std::unique_ptr<Box> & b2)
  {
    return (b1->getLength()*b1->getWidth()) < (b2->getLength()*b2->getWidth());
  }
};

#endif
