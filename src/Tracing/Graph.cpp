#include "Tracing/Graph.h"

namespace CityGen
{
Vertex::Vertex(Vector pos)
  : _pos(pos)
{
}

bool Vertex::removeEdge(const Edge &edge)
{
  const auto it = std::find(std::begin(_edges), std::end(_edges), edge);
  bool res = false;

  if (it != std::end(_edges))
  {
    _edges.erase(it);
    res = true;
  }

  return res;
}

Edge::Edge(const std::shared_ptr<Vertex> &a, const std::shared_ptr<Vertex> &b)
  : _a(a), _b(b)
{
  if (_a == nullptr || _b == nullptr)
  {
    throw std::invalid_argument{ "Vertices should not be nullptr." };
  }

  if (*_a == *_b)
  {
    throw std::invalid_argument{ "Cannot create an edge with two identical vertices." };
  }

  _direction = { _b->getPos() - _a->getPos() };

  _direction.normalize();
  _a->addEdge(*this);
  _b->addEdge(*this);
}
}