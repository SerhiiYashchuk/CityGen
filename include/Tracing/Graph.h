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
  using VDescriptor = typename boost::graph_traits<UnderlyingGraph>::vertex_descriptor;
  using EDescriptor = typename boost::graph_traits<UnderlyingGraph>::edge_descriptor;

  Graph() = default;
  Graph(const std::vector<VertexData> &verticesData);

  VDescriptor addVertex(const VertexData &vertexData);
  void removeVertex(VDescriptor vertex);
  std::vector<VDescriptor> getVertices() const;
  std::size_t getVerticesCount() const;

  std::vector<VDescriptor> getAdjacentVertices(VDescriptor vertex) const;

  VertexData &getData(VDescriptor vertex);
  const VertexData &getData(VDescriptor vertex) const;

  EDescriptor addEdge(VDescriptor vertex1, VDescriptor vertex2);
  void removeEdge(EDescriptor edge);
  void removeEdge(VDescriptor vertex1, VDescriptor vertex2);
  std::optional<EDescriptor> getEdge(VDescriptor vertex1, VDescriptor vertex2) const;
  std::vector<EDescriptor> getEdges() const;
  std::size_t getEdgesCount() const;

  VDescriptor getSource(EDescriptor edge) const;
  VDescriptor getTarget(EDescriptor edge) const;

private:
  UnderlyingGraph _graph;
};
}

#endif
