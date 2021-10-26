#ifndef THOUGHPACK_H
#define THOUGHPACK_H
#include <string>
#include <Box.h>

class ThoughPack : public Box
{
  using Box::Box;

public:
  ThoughPack(double lv, double wv, double hv, std::string mat);
  double volume() const override;                                  // Function to calculate the volume of a box

private:
  std::string material{"carton"};
};

#endif // THOUGHPACK_H
