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

Graph::Vertex Graph::addVertex(const Graph::VertexData &vertexData)
{
  return boost::add_vertex(vertexData, _graph);
}

void Graph::removeVertex(Graph::Vertex vertex)
{
  boost::clear_vertex(vertex, _graph);
  boost::remove_vertex(vertex, _graph);
}

std::vector<Graph::Vertex> Graph::getVertices() const
{
  std::vector<Graph::Vertex> vertices;

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

std::vector<Graph::Vertex> Graph::getAdjacentVertices(Graph::Vertex vertex) const
{
  std::vector<Graph::Vertex> adjacent;

  const auto adj = boost::adjacent_vertices(vertex, _graph);

  for (auto begin = adj.first, end = adj.second; begin != end; ++begin)
  {
    adjacent.push_back(*begin);
  }

  return adjacent;
}

Graph::VertexData &Graph::getData(Graph::Vertex vertex)
{
  return _graph[vertex];
}

const Graph::VertexData &Graph::getData(Graph::Vertex vertex) const
{
  return _graph[vertex];
}

Graph::Edge Graph::addEdge(Graph::Vertex vertex1, Graph::Vertex vertex2)
{
  return boost::add_edge(vertex1, vertex2, _graph).first;
}

void Graph::removeEdge(Graph::Edge edge)
{
  boost::remove_edge(edge, _graph);
}

void Graph::removeEdge(Graph::Vertex vertex1, Graph::Vertex vertex2)
{
  boost::remove_edge(vertex1, vertex2, _graph);
}

std::optional<Graph::Edge> Graph::getEdge(Graph::Vertex vertex1, Graph::Vertex vertex2) const
{
  std::optional<Graph::Edge> edge;
  const auto pair = boost::edge(vertex1, vertex2, _graph);

  if (pair.second)
  {
    edge = pair.first;
  }

  return edge;
}

std::vector<Graph::Edge> Graph::getEdges() const
{
  std::vector<Graph::Edge> edges;

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

Graph::Vertex Graph::getSource(Graph::Edge edge) const
{
  return boost::source(edge, _graph);
}

Graph::Vertex Graph::getTarget(Graph::Edge edge) const
{
  return boost::target(edge, _graph);
}
}