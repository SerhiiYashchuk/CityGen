#include <iostream>

#include "graphVisualization.h"

namespace CityGen 
{
  std::vector<Vector> getVerticesPositions(const Graph& graph)
  {
    std::vector<Graph::Vertex> vertices = graph.getVertices();
    
    std::vector<Vector> verticesPositions;

    for (const auto vertex : vertices)
    {
      verticesPositions.push_back(graph.getData(vertex));
    }
    return verticesPositions;
  }
  
  
  Vector getVertexPosition(const Graph& graph, const Graph::Vertex vertexIndex)
  {
    return graph.getData(vertexIndex);
  }


  sf::CircleShape createVertexShape(const Vector& position, const float radius, 
    const sf::Color color, const sf::Color borderColor)
  {
    sf::CircleShape vertex(radius);
    vertex.setPosition(position.x - radius, position.y - radius);
    
    vertex.setFillColor(color);
    vertex.setOutlineColor(borderColor);
    vertex.setOutlineThickness(radius / 10.0f);

    return vertex;
  }
    
  
  std::vector<sf::CircleShape> createVerticesShapes(const std::vector<Vector>& positions, const float radius,
    const sf::Color color, const sf::Color borderColor)
  {
    std::vector<sf::CircleShape> vertices;

    for (const auto position : positions)
    {
      vertices.push_back(createVertexShape(position, radius, color, borderColor));
    }
      
    return vertices;
  }


  std::vector<sf::VertexArray> createEdgesShapes(const std::vector<Graph::Edge>& edges,
    const std::vector<Vector>& verticesPositions, const float vertexRadius)
  {
    std::vector<sf::VertexArray> edgesShapes;

    for (size_t i = 0, s = edges.size(); i < s; ++i)
    {
      edgesShapes.push_back(sf::VertexArray(sf::Lines, 2));

      edgesShapes[i][0].position = sf::Vector2f(verticesPositions[edges[i].m_source].x, 
        verticesPositions[edges[i].m_source].y);
      edgesShapes[i][1].position = sf::Vector2f(verticesPositions[edges[i].m_target].x, 
        verticesPositions[edges[i].m_target].y);
    }

    return edgesShapes;
  }

  
  bool addVertexShape(sf::RenderWindow& window, sf::Vector2u windowSize, Graph& graph,
    std::vector<sf::CircleShape>& vertices, float radius, sf::Color color)
  {
    if (sf::Mouse::getPosition(window).x < windowSize.x - uiBlockWidth)
    {
      sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

      Graph::Vertex vertexIndex = graph.addVertex({ mousePosition.x,  mousePosition.y });

      Vector vertexPosition = getVertexPosition(graph, vertexIndex);
      sf::CircleShape vertex = createVertexShape(vertexPosition, radius, color);
      vertices.push_back(vertex);

      std::cout << "new vertex coord: (" << vertexPosition.x << ", " << vertexPosition.y << ")" << std::endl;
      return true;
    }
    else
    {
      return false;
    }
  }

  /*
  Graph::Vertex selectVertex(sf::RenderWindow& window, const std::vector<Vector>& verticesPositions, float vertexRadius)
  {
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    

  }
  */


  void drawVertices(sf::RenderWindow& window, const std::vector<sf::CircleShape>& vertices)
  {
    for (const auto vertex : vertices)
    {
      window.draw(vertex);
    }
  }


  void drawEdges(sf::RenderWindow& window, const std::vector<sf::VertexArray>& edges)
  {
    for (const auto edge : edges)
    {
      window.draw(edge);
    }
  }
  

  void drawGraph(sf::RenderWindow& window, const std::vector<sf::CircleShape>& vertices,
    const std::vector<sf::VertexArray>& edges)
  {
    drawVertices(window, vertices);
    drawEdges(window, edges);
  }
}
