#include "Tracing/RegionBuilder.h"
#include <algorithm>
#include <iterator>
#include <cassert>

namespace
{
float signedAngle(CityGen::Vector v1, CityGen::Vector v2)
{
  const float dotProduct = CityGen::Vector::dotProduct(v1, v2);
  const float cross = v1.x * v2.y - v1.y * v2.x;

  return std::atan2(cross, dotProduct);
}

void removeDeadEnds(std::vector<CityGen::Graph::Vertex> &vertices)
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
}

namespace CityGen
{
RegionBuilder::RegionBuilder(const Graph &graph) : _graph(graph)
{
  
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

std::optional<Region> RegionBuilder::walkRegionBoundary(Graph::Edge start, bool moveStreight)
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
  std::vector<Graph::Vertex> vertices;
  Graph::Edge e = start;

  do
  {
    // TODO: consider using swap() and pop_back() to delete elements
    const auto upIt = std::find(std::begin(_unprocessedEdges), std::end(_unprocessedEdges), e);

    if (upIt != std::end(_unprocessedEdges))
    {
      _unprocessedEdges.erase(upIt);
      _halfProcessedEdges.emplace_back(e, !moveStreight);
    }
    else
    {
      const auto hpIt = std::find(std::begin(_halfProcessedEdges), std::end(_halfProcessedEdges),
        std::make_pair(e, moveStreight));
      
      if (hpIt != std::end(_halfProcessedEdges))
      {
        _halfProcessedEdges.erase(hpIt);
      }
      else
      {
        return region;
      }
    }

    vertices.push_back(moveStreight ? _graph.getTarget(e) : _graph.getSource(e));

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
      points.push_back(_graph.getData(vertex));
    }

    region = Region{ points };
  }

  return region;
}

std::optional<std::pair<Graph::Edge, bool>> RegionBuilder::walkNextEdge(Graph::Edge edge,
  bool moveStreight)
{
  std::optional<std::pair<Graph::Edge, bool>> nextEdge;

  const auto source = _graph.getSource(edge);
  const auto target = _graph.getTarget(edge);
  const auto vertex = moveStreight ? target : source;
  const auto opposite = moveStreight ? source : target;
  const auto adjVertices = _graph.getAdjacentVertices(vertex);
  const std::size_t edgesCount = adjVertices.size();

  switch (edgesCount)
  {
    case 0:
      break;

    case 1:
      nextEdge = std::make_pair(edge, !moveStreight);
      break;

    case 2:
    {
      const auto nextVertex = adjVertices.front() == opposite ? adjVertices.back() : adjVertices.front();
      const auto e = _graph.getEdge(vertex, nextVertex);
      const bool streight = _graph.getSource(*e) == vertex;

      nextEdge = std::make_pair(*e, streight);
    }
      break;

    default:
    {
      Vector direction = (_graph.getData(target) - _graph.getData(source)) * (moveStreight ? 1.f : -1.f);

     direction.normalize();

      const auto minIt = std::min_element(std::begin(adjVertices), std::end(adjVertices),
      [direction, vertex, opposite, this](const auto lhs, const auto rhs)
      {
        // If a vertex is one of passed in edge's ends
        if (lhs == opposite)
        {
          return false;
        }

        const auto lhsEdge = _graph.getEdge(vertex, lhs);
        const auto lhsSource = _graph.getSource(*lhsEdge);
        const auto lhsTarget = lhsSource == vertex ? lhs : vertex;
        const bool lhsStreight = lhsSource == vertex;
        const Vector lhsDirection = (_graph.getData(lhsTarget) - _graph.getData(lhsSource))
          * (lhsStreight ? 1.f : -1.f);
        const float angleToLhs = signedAngle(direction, lhsDirection * (lhsStreight ? 1.f : -1.f));

        const auto rhsEdge = _graph.getEdge(vertex, rhs);
        const auto rhsSource = _graph.getSource(*rhsEdge);
        const auto rhsTarget = rhsSource == vertex ? rhs : vertex;
        const bool rhsStreight = rhsSource == vertex;
        const Vector rhsDirection = (_graph.getData(rhsTarget) - _graph.getData(rhsSource))
          * (rhsStreight ? 1.f : -1.f);
        const float angleToRhs = signedAngle(direction, rhsDirection * (rhsStreight ? 1.f : -1.f));

        return angleToLhs < angleToRhs;
      });

      const auto e = _graph.getEdge(vertex, *minIt);
      nextEdge = std::make_pair(*e, _graph.getSource(*e) == vertex);
    }
  }

  return nextEdge;
}
}
