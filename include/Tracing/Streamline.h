#ifndef CITYGEN_STREAMLINE_H
#define CITYGEN_STREAMLINE_H

#include "GenericTypes.h"
#include "Tracing/Graph.h"
#include <unordered_set>

namespace CityGen
{
class Streamline
{
public:
  Streamline(const std::shared_ptr<Vertex> &start);

  const std::shared_ptr<Vertex> &getFirst() const
  {
    return _first;
  }

  const std::shared_ptr<Vertex> &getLast() const
  {
    return _last;
  }

  bool addVertex(const std::shared_ptr<Vertex> &vertex)
  {
    return _vertices.insert(vertex).second;
  }

  bool removeVertex(const std::shared_ptr<Vertex> &vertex)
  {
    return _vertices.erase(vertex) != 0;
  }

  bool containsVertex(const std::shared_ptr<Vertex> &vertex) const
  {
    return _vertices.find(vertex) != std::end(_vertices);
  }

  Edge extand(const std::shared_ptr<Vertex> &vertex);

private:
  std::shared_ptr<Vertex> _first;
  std::shared_ptr<Vertex> _last;

  std::unordered_set<std::shared_ptr<Vertex>> _vertices;
};
}

#endif
