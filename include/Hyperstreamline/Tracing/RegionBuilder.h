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
  std::optional<Region> walkRegionBoundary(Graph::Edge start, bool moveStreight = true);
  std::optional<std::pair<Graph::Edge, bool>> walkNextEdge(Graph::Edge edge,
    bool moveStreight = true);

  std::vector<Graph::Edge> _unprocessedEdges;
  std::vector<std::pair<Graph::Edge, bool>> _halfProcessedEdges;
  std::vector<Region> _regions;
  const Graph &_graph;
  bool _regionsBuilt = false;
};
}

#endif
