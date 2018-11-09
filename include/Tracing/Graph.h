#ifndef CITYGEN_GRAPH_H
#define CITYGEN_GRAPH_H

#include "GenericTypes.h"
#include <vector>
#include <memory>

namespace CityGen
{
class Edge;

class Vertex
{
public:
  explicit Vertex(Vector pos);
  ~Vertex();

  Vector getPos() const
  {
    return _pos;
  }

  const std::vector<Edge> &getEdges() const
  {
    return _edges;
  }

  void addEdge(const Edge &edge)
  {
    _edges.push_back(edge);
  }

  bool removeEdge(const Edge &edge);

  std::size_t getEdgesCount() const
  {
    return _edges.size();
  }

  bool operator==(const Vertex &rhs) const
  {
    return _pos == rhs._pos && _edges == rhs._edges;
  }

private:
  const Vector _pos;

  std::vector<Edge> _edges;
};

class Edge
{
public:
  Edge(const std::shared_ptr<Vertex> &a, const std::shared_ptr<Vertex> &b);

  const std::shared_ptr<Vertex> &getA() const
  {
    return _a.lock();
  }

  const std::shared_ptr<Vertex> &getB() const
  {
    return _b.lock();
  }

  Vector getDirection() const
  {
    return _direction;
  }

  bool operator==(const Edge &rhs) const
  {
    return _a.lock() == rhs._a.lock() && _b.lock() == rhs._b.lock() && _direction == rhs._direction;
  }

  bool operator!=(const Edge &rhs) const
  {
    return !(*this == rhs);
  }

private:
  std::weak_ptr<Vertex> _a;
  std::weak_ptr<Vertex> _b;
  Vector _direction;
};

namespace Utils
{
std::pair<Edge, Edge> splitEdge(const Edge &edge, const std::shared_ptr<Vertex> &mid)
{
  return { Edge{ edge.getA(), mid }, Edge{ mid, edge.getB() } };
}
}
}

#endif
