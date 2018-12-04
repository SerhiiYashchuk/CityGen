#include "Tracing/Streamline.h"
#include <algorithm>
#include <cassert>

namespace CityGen
{
Streamline::Streamline(const Graph &graph, Graph::Vertex start)
  : _first(start), _last(start), _graph(graph)
{
}

std::pair<Graph::Vertex, Graph::Vertex> Streamline::extend(Graph::Vertex vertex)
{
  if (vertex != _first && !addVertex(vertex))
  {
    assert(false);
  }

  const auto a = _last;
  const auto b = vertex;
  const auto adjacent = _graph.getAdjacentVertices(_last);

  if (std::find(std::begin(adjacent), std::end(adjacent), vertex) != std::end(adjacent))
  {
    assert(false);
  }

  _last = vertex;

  return { a, b };
}
}