+#ifndef TRUCKLOAD_H
#define TRUCKLOAD_H
#include <vector>
#include <memory>
#include <functional>
class Box;
class TruckLoad
{
public:
  TruckLoad(float maxDim = 2.5f);
  TruckLoad(const TruckLoad& other);
  void addBox(std::unique_ptr<Box> box);
  const std::unique_ptr<Box> & largestBox() const;
  std::unique_ptr<Box> &operator [](unsigned int index);
  const std::unique_ptr<Box> &operator [](unsigned int index) const;
  void sortLoad();
  void sortLoad(std::function<bool(const std::unique_ptr<Box> &, const std::unique_ptr<Box> &)> compBox);
  bool checkLoad();

private:
  float maxDimension;
  std::vector<std::unique_ptr<Box>> load;
};

#endif // TRUCKLOAD_H
