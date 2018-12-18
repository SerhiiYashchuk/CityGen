#include "GraphVisualization.h"

namespace CityGen 
{
  std::vector<Vector> getVerticesPositions(const Graph & graph)
  {
    std::vector<Graph::Vertex> vertices = graph.getVertices();

    std::vector<Vector> verticesPositions;

  for(const auto vertex : vertices)
    {
      verticesPositions.push_back(graph.getData(vertex));
    }

    return verticesPositions;
  }

  std::vector<sf::CircleShape> createVertices(const std::vector<Vector> & verticesPositions,
    sf::Color color, float vertexSize)
  {
    std::vector<sf::CircleShape> vertices;

  for (const auto vertexPosition : verticesPositions)
  {
    sf::CircleShape vertex(vertexSize);
    vertex.setPosition(vertexPosition.x, vertexPosition.y);
    vertex.setFillColor(color);

    vertices.push_back(vertex);
  }

    return vertices;
  }

  std::vector<sf::VertexArray> createEdges(const std::vector<Graph::Edge> & edges,
    const std::vector<Vector> & verticesPositions, float vertexRadius)
  {
    std::vector<sf::VertexArray> edgesPositions;

    for (size_t i = 0, s = edges.size(); i < s; i++)
    {
      edgesPositions.push_back(sf::VertexArray(sf::Lines, 2));

      edgesPositions[i][0].position = sf::Vector2f(verticesPositions[edges[i].m_source].x + vertexRadius, verticesPositions[edges[i].m_source].y + vertexRadius);
      edgesPositions[i][1].position = sf::Vector2f(verticesPositions[edges[i].m_target].x + vertexRadius, verticesPositions[edges[i].m_target].y + vertexRadius);
    }

    return edgesPositions;
  }

  void drawEdges(sf::RenderWindow& window, std::vector<sf::VertexArray> edges)
  {
    for (size_t i = 0, s = edges.size(); i < s; i++)
    {
      window.draw(edges[i]);
    }
  }

  void drawVertices(sf::RenderWindow& window, std::vector<sf::CircleShape> vertices)
  {
    for (size_t i = 0, s = vertices.size(); i < s; i++)
    {
      window.draw(vertices[i]);
    }
  }

}
