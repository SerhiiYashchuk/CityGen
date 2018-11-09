#include "Tracing/Streamline.h"
#include <algorithm>
#include <cassert>

namespace CityGen
{
Streamline::Streamline(const std::shared_ptr<Vertex> &start)
  : _first(start), _last(start)
{
}

Edge Streamline::extand(const std::shared_ptr<Vertex> &vertex)
{
  if (vertex != _first && !addVertex(vertex))
  {
    assert(false);
  }

  const auto &a = _last;
  const auto &b = vertex;

  if (std::any_of(std::begin(a->getEdges()), std::end(a->getEdges()), [a, b](const Edge &edge)
  {
    return a == edge.getA() && b == edge.getB() || a == edge.getB() && b == edge.getA();
  }))
  {
    assert(false);
  }

  _last = b;

  return { a, b };
}
}