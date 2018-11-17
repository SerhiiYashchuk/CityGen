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
  Streamline(const Graph &graph, Graph::VDescriptor start);

  Graph::VDescriptor getFirst() const
  {
    return _first;
  }

  Graph::VDescriptor getLast() const
  {
    return _last;
  }

  bool addVertex(Graph::VDescriptor vertex)
  {
    return _vertices.insert(vertex).second;
  }

  bool removeVertex(Graph::VDescriptor vertex)
  {
    return _vertices.erase(vertex) != 0;
  }

  bool containsVertex(Graph::VDescriptor vertex) const
  {
    return _vertices.find(vertex) != std::end(_vertices);
  }

  std::pair<Graph::VDescriptor, Graph::VDescriptor> extend(Graph::VDescriptor vertex);

private:
  Graph::VDescriptor _first;
  Graph::VDescriptor _last;
  std::unordered_set<Graph::VDescriptor> _vertices;

  const Graph &_graph;
};
}

#endif
