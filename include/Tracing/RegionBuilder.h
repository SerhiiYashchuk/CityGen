#ifndef CITYGEN_REGION_BUILDER_H
#define CITYGEN_REGION_BUILDER_H

#include "Tracing/Graph.h"
#include "Tracing/Region.h"
#include <unordered_set>
#include <optional>

namespace CityGen
{
class RegionBuilder
{
public:
  RegionBuilder(const std::vector<Vertex> &vertices);

  const std::vector<Region> &getRegions();

private:
  void buildRegions();
  std::optional<Region> walkRegionBoundary(const Edge &start, bool moveStreight = true);

  std::unordered_set<Edge> _unprocessedEdges;
  std::vector<std::pair<Edge, bool>> _halfProcessedEdges;
  std::vector<Region> _regions;
  bool _regionsBuilt = false;
};
}

#endif
