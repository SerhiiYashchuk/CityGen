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

  Vector getVertexPosition(const Graph & graph, Graph::Vertex vertexIndex)
  {
	  return graph.getData(vertexIndex);
  }

  std::vector<sf::CircleShape> createVertices(const std::vector<Vector> & verticesPositions,
   const sf::Color color, const float vertexRadius)
  {
    std::vector<sf::CircleShape> vertices;

  for (const auto vertexPosition : verticesPositions)
  {
    vertices.push_back(createVertex(vertexPosition, color, vertexRadius));
  }

    return vertices;
  }

  sf::CircleShape createVertex(const Vector& vertexPosition, const sf::Color color, const float vertexRadius)
  {
	  sf::CircleShape vertex(vertexRadius);
	  vertex.setPosition(vertexPosition.x - vertexRadius, vertexPosition.y - vertexRadius);
	  vertex.setFillColor(color);

	  vertex.setOutlineThickness(vertexRadius/10.0f);
	  vertex.setOutlineColor(sf::Color::White);

	  return vertex;
  }

  std::vector<sf::VertexArray> createEdges(const std::vector<Graph::Edge> & edges,
    const std::vector<Vector> & verticesPositions, const float vertexRadius)
  {
    std::vector<sf::VertexArray> edgesPositions;

    for (size_t i = 0, s = edges.size(); i < s; i++)
    {
      edgesPositions.push_back(sf::VertexArray(sf::Lines, 2));

      edgesPositions[i][0].position = sf::Vector2f(verticesPositions[edges[i].m_source].x, verticesPositions[edges[i].m_source].y);
      edgesPositions[i][1].position = sf::Vector2f(verticesPositions[edges[i].m_target].x, verticesPositions[edges[i].m_target].y);
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
