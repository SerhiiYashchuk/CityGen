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
  Vertex(Vector pos);

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
    return _a;
  }

  const std::shared_ptr<Vertex> &getB() const
  {
    return _b;
  }

  Vector getDirection() const
  {
    return _direction;
  }

private:
  std::shared_ptr<Vertex> _a;
  std::shared_ptr<Vertex> _b;
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
