#ifndef CITYGEN_GRAPH_H
#define CITYGEN_GRAPH_H

#include "GenericTypes.h"
#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <optional>

namespace CityGen
{
class Graph
{
public:
  using VertexData = Vector;
  using UnderlyingGraph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexData>;
  using Vertex = typename boost::graph_traits<UnderlyingGraph>::vertex_descriptor;
  using Edge = typename boost::graph_traits<UnderlyingGraph>::edge_descriptor;

  Graph() = default;
  Graph(const std::vector<VertexData> &verticesData);

  Vertex addVertex(const VertexData &vertexData);
  void removeVertex(Vertex vertex);
  std::vector<Vertex> getVertices() const;
  std::size_t getVerticesCount() const;

  std::vector<Vertex> getAdjacentVertices(Vertex vertex) const;

  VertexData &getData(Vertex vertex);
  const VertexData &getData(Vertex vertex) const;

  Edge addEdge(Vertex vertex1, Vertex vertex2);
  void removeEdge(Edge edge);
  void removeEdge(Vertex vertex1, Vertex vertex2);
  std::optional<Edge> getEdge(Vertex vertex1, Vertex vertex2) const;
  std::vector<Edge> getEdges() const;
  std::size_t getEdgesCount() const;

  Vertex getSource(Edge edge) const;
  Vertex getTarget(Edge edge) const;

private:
  UnderlyingGraph _graph;
};
}

#endif
