#include "Tracing/Region.h"
#include <algorithm>

namespace
{
enum class Orientation { Colinear, Clockwise, Counterclockwise };

bool pointIsOnSegment(CityGen::Vector begin, CityGen::Vector end, CityGen::Vector p)
{
  return p.x <= std::max(begin.x, end.x) && p.x >= std::min(begin.x, end.x) &&
    p.y <= std::max(begin.y, end.y) && p.y >= std::min(begin.y, end.y);
}

Orientation orientation(CityGen::Vector begin, CityGen::Vector end, CityGen::Vector p)
{
  const float val = (p.y - begin.y) * (end.x - p.x) - (p.x - begin.x) * (end.y - p.y);

  if (CityGen::Utils::almostEqual(val, 0.f))
  {
    return Orientation::Colinear;
  }

  return val > 0 ? Orientation::Clockwise : Orientation::Counterclockwise;
}

bool doIntersect(CityGen::Vector begin1, CityGen::Vector end1, CityGen::Vector begin2, CityGen::Vector end2)
{
  const Orientation o1 = orientation(begin1, end1, begin2);
  const Orientation o2 = orientation(begin1, end1, end2);
  const Orientation o3 = orientation(begin2, end2, begin1);
  const Orientation o4 = orientation(begin2, end2, end1);

  if (o1 != o2 && o3 != o4)
  {
    return true;
  }

  // begin1, end1 and begin2 are colinear and begin2 lies on segment begin1-end1
  if (o1 == Orientation::Colinear && pointIsOnSegment(begin1, end1, begin2))
  {
    return true;
  }

  // begin1, end1 and begin2 are colinear and end2 lies on segment begin1-end1
  if (o2 == Orientation::Colinear && pointIsOnSegment(begin1, end1, end2))
  {
    return true;
  }

  // begin2, end2 and begin1 are colinear and begin1 lies on segment begin2-end2
  if (o3 == Orientation::Colinear && pointIsOnSegment(begin2, end2, begin1))
  {
    return true;
  }

  // begin2, end2 and end1 are colinear and end1 lies on segment begin2-end2
  if (o4 == Orientation::Colinear && pointIsOnSegment(begin2, end2, end1))
  {
    return true;
  }

  return false;
}
}

namespace CityGen
{
Region::Region(std::vector<Vector> vertices)
  : _vertices(vertices)
{
  if (!_vertices.empty())
  {
    const auto xMinMax = std::minmax_element(std::begin(_vertices), std::end(_vertices),
      [](const auto &lhs, const auto &rhs) { return lhs.x < rhs.x; });
    const auto yMinMax = std::minmax_element(std::begin(_vertices), std::end(_vertices),
      [](const auto &lhs, const auto &rhs) { return lhs.y < rhs.y; });
    
    _min = { xMinMax.first->x, yMinMax.first->y };
    _max = { xMinMax.second->x, yMinMax.second->y };
  }
}

bool Region::isClockwise() const
{
  float sum{};

  for (std::size_t i = 0; i < _vertices.size(); ++i)
  {
    const Vector &a = _vertices[i];
    const Vector &b = _vertices[(i + 1) % _vertices.size()];
    const float n = (b.x - a.x) * (b.y + a.y);

    sum += n;
  }

  return sum > 0;
}

bool Region::containsPoint(Vector p) const
{
  const std::size_t n = _vertices.size();
  // Not enough points to make a region
  if (n < 3)
  {
    return false;
  }

  const Vector extreme = { _max.x + 1, p.y };
  std::size_t count = 0;

  for (std::size_t i = 0; i < n; ++i)
  {
    const auto &v1 = _vertices[i];
    const auto &v2 = _vertices[(i + 1) % n];

    if (doIntersect(v1, v2, p, extreme))
    {
      if (orientation(v1, v2, p) == Orientation::Colinear)
      {
        return pointIsOnSegment(v1, v2, p);
      }

      ++count;
    }
  }

  return count % 2 != 0;
}

void Region::flip()
{
  std::reverse(std::begin(_vertices), std::end(_vertices));
}
}
