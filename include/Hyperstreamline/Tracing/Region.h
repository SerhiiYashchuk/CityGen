#ifndef CITYGEN_REGION_H
#define CITYGEN_REGION_H

#include "GenericTypes.h"
#include <vector>

namespace CityGen
{
class Region
{
public:
  explicit Region(std::vector<Vector> vertices);

  const std::vector<Vector> &getVertices() const
  {
    return _vertices;
  }

  Vector getMin() const
  {
    return _min;
  }

  Vector getMax() const
  {
    return _max;
  }

  bool isClockwise() const;
  bool containsPoint(Vector p) const;

  void flip();

private:
  std::vector<Vector> _vertices;
  Vector _min;
  Vector _max;
};
}

#endif
