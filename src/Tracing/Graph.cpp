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
  if (a == nullptr || b == nullptr)
  {
    throw std::invalid_argument{ "Vertices should not be nullptr." };
  }

  if (*a == *b)
  {
    throw std::invalid_argument{ "Cannot create an edge with two identical vertices." };
  }

  _direction = { b->getPos() - a->getPos() };

  _direction.normalize();
  a->addEdge(*this);
  b->addEdge(*this);
}
}