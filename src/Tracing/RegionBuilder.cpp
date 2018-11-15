#include "Tracing/RegionBuilder.h"
#include <algorithm>
#include <iterator>
#include <cassert>

namespace
{
float signedAngle(CityGen::Vector v1, CityGen::Vector v2)
{
  const float dotProduct = CityGen::Utils::dotProduct(v1, v2);
  const float cross = v1.x * v2.y - v1.y * v2.x;

  return std::atan2(cross, dotProduct);
}

void removeDeadEnds(std::vector<std::shared_ptr<CityGen::Vertex>> &vertices)
{
  // First step: remove consecutive copies of the same vertices
  // TODO: should we compare exact vertices instead of pointers?
  vertices.erase(std::unique(std::begin(vertices), std::end(vertices)), std::end(vertices));

  if (vertices.front() == vertices.back())
  {
    vertices.pop_back();
  }

  // Second step: remove actual dead ends
  // Example: v1-v2-v1 will result in just v1
  // TODO: Is there more robust way to do this?
  for (std::size_t i = 0; i < vertices.size(); ++i)
  {
    const auto it1 = std::next(std::begin(vertices), i);
    const auto it2 = std::next(std::begin(vertices), (i + 1) % vertices.size());
    const auto it3 = std::next(std::begin(vertices), (i + 2) % vertices.size());

    if (*it1 == *it3)
    {
      vertices.erase(it2);
      vertices.erase(it3);
    }
  }
}

std::optional<std::pair<CityGen::Edge, bool>> walkNextEdge(const CityGen::Edge &edge, bool moveStreight = true)
{
  std::optional<std::pair<CityGen::Edge, bool>> nextEdge;
  auto vertex = moveStreight ? edge.getB() : edge.getA();

  if (vertex != nullptr)
  {
    const std::size_t edgesCount = vertex->getEdgesCount();

    if (edgesCount == 0)
    {
      return nextEdge;
    }

    if (edgesCount == 1)
    {
      return std::make_pair(edge, !moveStreight);
    }

    const auto &edges = vertex->getEdges();

    if (edgesCount == 2)
    {
      const auto &next = edges.front() == edge ? edges.back() : edges.front();
      const bool streight = next.getA() == vertex;

      return std::make_pair(next, streight);
    }

    const CityGen::Vector direction = edge.getDirection() * (moveStreight ? 1.f : -1.f);

    for (const auto &e : edges)
    {
      if (e == edge)
      {
        continue;
      }

      const bool isStart = e.getA() == vertex;
      const float angle = signedAngle(direction, e.getDirection() * (isStart ? 1.f : -1.f));
    }

    const auto minIt = std::min_element(std::begin(edges), std::end(edges),
    [direction, &edge, &vertex](const auto &lhs, const auto &rhs)
    {
      if (lhs == edge)
      {
        return false;
      }

      const bool lhsStreight = lhs.getA() == vertex;
      const bool rhsStreight = rhs.getA() == vertex;
      const float angleToLhs = signedAngle(direction, lhs.getDirection() * (lhsStreight ? 1 : -1));
      const float angleToRhs = signedAngle(direction, rhs.getDirection() * (rhsStreight ? 1 : -1));

      return angleToLhs < angleToRhs;
    });
    nextEdge = std::make_pair(*minIt, minIt->getA() == vertex);
  }

  return nextEdge;
}
}

namespace CityGen
{
RegionBuilder::RegionBuilder(const std::vector<Vertex> &vertices)
{
  std::for_each(std::begin(vertices), std::end(vertices), [this](const Vertex &vertex)
  {
    std::copy(std::begin(vertex.getEdges()), std::end(vertex.getEdges()),
    std::inserter(_unprocessedEdges, std::end(_unprocessedEdges)));
  });
}

const std::vector<Region> &RegionBuilder::getRegions()
{
  if (!_regionsBuilt)
  {
    buildRegions();
  }

  return _regions;
}

void RegionBuilder::buildRegions()
{
  while (_unprocessedEdges.size() > 0 && _halfProcessedEdges.size() > 0)
  {
    std::optional<Region> boundary;

    if (_halfProcessedEdges.size() > 0)
    {
      const auto &p = _halfProcessedEdges.front();
      boundary = walkRegionBoundary(p.first, p.second);
    }
    else if (_unprocessedEdges.size() > 0)
    {
      boundary = walkRegionBoundary(*_unprocessedEdges.begin());
    }
    else
    {
      break;
    }

    if (boundary)
    {
      _regions.emplace_back(*boundary);
    }
  }

  _regionsBuilt = true;
}

std::optional<Region> RegionBuilder::walkRegionBoundary(const Edge &start, bool moveStreight)
{
  // TODO: implement
  /*
  if (start.Streamline.Width == 0)
  {
    halfProcessed.Remove(new KeyValuePair<bool, Edge>(true, start));
    halfProcessed.Remove(new KeyValuePair<bool, Edge>(false, start));
    unprocessed.Remove(start);
    return null;
  }
  */

  std::optional<Region> region;
  std::vector<std::shared_ptr<Vertex>> vertices;
  Edge e = start;

  do
  {
    if (_unprocessedEdges.erase(e) != 0)
    {
      _halfProcessedEdges.emplace_back(e, !moveStreight);
    }
    else
    {
      const auto it = std::find(std::begin(_halfProcessedEdges), std::end(_halfProcessedEdges),
        std::make_pair(e, moveStreight));
      
      if (it != std::end(_halfProcessedEdges))
      {
        _halfProcessedEdges.erase(it);
      }
      else
      {
        return region;
      }
    }

    const auto &vertex = moveStreight ? e.getB() : e.getA();

    assert(vertex != nullptr);
    vertices.emplace_back(vertex);

    if (auto next = walkNextEdge(e, moveStreight))
    {
      std::tie(e, moveStreight) = *next;
    }
    else
    {
      return region;
    }
  }
  while (e != start);

  removeDeadEnds(vertices);

  if (vertices.size() >= 3)
  {
    std::vector<Vector> points;

    for (const auto &vertex : vertices)
    {
      points.emplace_back(vertex->getPos());
    }

    region = Region{ points };
  }

  return region;
}
}
