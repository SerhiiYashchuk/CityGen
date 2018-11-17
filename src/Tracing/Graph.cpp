#include "Tracing/Graph.h"

namespace CityGen
{
Graph::Graph(const std::vector<Graph::VertexData> &verticesData)
{
  for (const auto &data : verticesData)
  {
    boost::add_vertex(data, _graph);
  }
}

Graph::VDescriptor Graph::addVertex(const Graph::VertexData &vertexData)
{
  return boost::add_vertex(vertexData, _graph);
}

void Graph::removeVertex(Graph::VDescriptor vertex)
{
  boost::clear_vertex(vertex, _graph);
  boost::remove_vertex(vertex, _graph);
}

std::vector<Graph::VDescriptor> Graph::getVertices() const
{
  std::vector<Graph::VDescriptor> vertices;

  const auto vert = boost::vertices(_graph);

  for (auto begin = vert.first, end = vert.second; begin != end; ++begin)
  {
    vertices.push_back(*begin);
  }

  return vertices;
}

std::size_t Graph::getVerticesCount() const
{
  return boost::num_vertices(_graph);
}

std::vector<Graph::VDescriptor> Graph::getAdjacentVertices(Graph::VDescriptor vertex) const
{
  std::vector<Graph::VDescriptor> adjacent;

  const auto adj = boost::adjacent_vertices(vertex, _graph);

  for (auto begin = adj.first, end = adj.second; begin != end; ++begin)
  {
    adjacent.push_back(*begin);
  }

  /*std::for_each(adj.first, adj.second, [&adjacent](const auto &it)
  {
    adjacent.push_back(*it);
  });*/

  return adjacent;
}

Graph::VertexData &Graph::getData(Graph::VDescriptor vertex)
{
  return _graph[vertex];
}

const Graph::VertexData &Graph::getData(Graph::VDescriptor vertex) const
{
  return _graph[vertex];
}

Graph::EDescriptor Graph::addEdge(Graph::VDescriptor vertex1, Graph::VDescriptor vertex2)
{
  return boost::add_edge(vertex1, vertex2, _graph).first;
}

void Graph::removeEdge(Graph::EDescriptor edge)
{
  boost::remove_edge(edge, _graph);
}

void Graph::removeEdge(Graph::VDescriptor vertex1, Graph::VDescriptor vertex2)
{
  boost::remove_edge(vertex1, vertex2, _graph);
}

std::optional<Graph::EDescriptor> Graph::getEdge(Graph::VDescriptor vertex1, Graph::VDescriptor vertex2) const
{
  std::optional<Graph::EDescriptor> edge;
  const auto pair = boost::edge(vertex1, vertex2, _graph);

  if (pair.second)
  {
    edge = pair.first;
  }

  return edge;
}

std::vector<Graph::EDescriptor> Graph::getEdges() const
{
  std::vector<Graph::EDescriptor> edges;

  const auto e = boost::edges(_graph);

  for (auto begin = e.first, end = e.second; begin != end; ++begin)
  {
    edges.push_back(*begin);
  }

  return edges;
}

std::size_t Graph::getEdgesCount() const
{
  return boost::num_edges(_graph);
}

Graph::VDescriptor Graph::getSource(Graph::EDescriptor edge) const
{
  return boost::source(edge, _graph);
}

Graph::VDescriptor Graph::getTarget(Graph::EDescriptor edge) const
{
  return boost::target(edge, _graph);
}
}