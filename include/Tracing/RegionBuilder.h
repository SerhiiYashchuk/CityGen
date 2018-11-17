#ifndef CITYGEN_REGION_BUILDER_H
#define CITYGEN_REGION_BUILDER_H

#include "Tracing/Graph.h"
#include "Tracing/Region.h"
#include <optional>

namespace CityGen
{
class RegionBuilder
{
public:
  RegionBuilder(const Graph &graph);

  const std::vector<Region> &getRegions();

private:
  void buildRegions();
  std::optional<Region> walkRegionBoundary(Graph::EDescriptor start, bool moveStreight = true);
  std::optional<std::pair<Graph::EDescriptor, bool>> walkNextEdge(Graph::EDescriptor edge,
    bool moveStreight = true);

  std::vector<Graph::EDescriptor> _unprocessedEdges;
  std::vector<std::pair<Graph::EDescriptor, bool>> _halfProcessedEdges;
  std::vector<Region> _regions;
  const Graph &_graph;
  bool _regionsBuilt = false;
};
}

#endif
