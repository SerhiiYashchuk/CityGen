#ifndef CITYGEN_STREAMLINE_H
#define CITYGEN_STREAMLINE_H

#include "GenericTypes.h"
#include "Tracing/Graph.h"
#include <unordered_set>
#include <utility>

namespace CityGen
{
class Streamline
{
public:
  Streamline(const Graph &graph, Graph::Vertex start);

  Graph::Vertex getFirst() const
  {
    return _first;
  }

  Graph::Vertex getLast() const
  {
    return _last;
  }

  bool addVertex(Graph::Vertex vertex)
  {
    return _vertices.insert(vertex).second;
  }

  bool removeVertex(Graph::Vertex vertex)
  {
    return _vertices.erase(vertex) != 0;
  }

  bool containsVertex(Graph::Vertex vertex) const
  {
    return _vertices.find(vertex) != std::end(_vertices);
  }

  std::pair<Graph::Vertex, Graph::Vertex> extend(Graph::Vertex vertex);

private:
  Graph::Vertex _first;
  Graph::Vertex _last;
  std::unordered_set<Graph::Vertex> _vertices;

  const Graph &_graph;
};
}

#endif
