#include <graphVisualization.h>

namespace CityGen 
{
  std::vector<CityGen::Vector> getVerticesPositions(const CityGen::Graph & graph)
  {
    std::vector<CityGen::Graph::Vertex> vertices = graph.getVertices();

    std::vector<CityGen::Vector> verticesPositions;

    for (size_t i = 0, s = vertices.size(); i < s; i++)
    {
      verticesPositions.push_back(graph.getData(vertices[i]));
    }

    return verticesPositions;
  }

  std::vector<sf::CircleShape> createVertices(const CityGen::Graph & graph,
    sf::Color color, float vertexSize)
  {
    std::vector<CityGen::Vector> verticesPositions = getVerticesPositions(graph);

    std::vector<sf::CircleShape> vertices;

    for (size_t i = 0, s = verticesPositions.size(); i < s; i++)
    {
      sf::CircleShape vertex(vertexSize);
      vertex.setPosition(verticesPositions[i].x, verticesPositions[i].y);
      vertex.setFillColor(color);

      vertices.push_back(vertex);
    }

    return vertices;
  }

  std::vector<sf::VertexArray> getEdgesPositions(const CityGen::Graph & graph, float vertexRadius)
  {
    std::vector<CityGen::Vector> verticesPositions = getVerticesPositions(graph);

    std::vector<CityGen::Graph::Edge> edges = graph.getEdges();

    std::vector<sf::VertexArray> edgesPositions;

    for (size_t i = 0, s = edges.size(); i < s; i++)
    {
      edgesPositions.push_back(sf::VertexArray(sf::Lines, 2));

      edgesPositions[i][0].position = sf::Vector2f(verticesPositions[edges[i].m_source].x + vertexRadius, verticesPositions[edges[i].m_source].y + vertexRadius);
      edgesPositions[i][1].position = sf::Vector2f(verticesPositions[edges[i].m_target].x + vertexRadius, verticesPositions[edges[i].m_target].y + vertexRadius);
    }

    return edgesPositions;
  }

  void drawVertices(sf::RenderWindow& window, std::vector<sf::CircleShape> vertices)
  {
    for (size_t i = 0, s = vertices.size(); i < s; i++)
    {
      window.draw(vertices[i]);
    }
  }

  void drawEdges(sf::RenderWindow& window, std::vector<sf::VertexArray> edges)
  {
    for (size_t i = 0, s = edges.size(); i < s; i++)
    {
      window.draw(edges[i]);
    }
  }
}
