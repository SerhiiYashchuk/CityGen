#include "Hyperstreamline/Tracing/Graph.h"
#include <SFML/Graphics.hpp>
#include "UI.h"

namespace CityGen 
{  
  std::vector<Vector> getVerticesPositions(const Graph& graph);
  Vector getVertexPosition(const Graph& graph, const Graph::Vertex vertexIndex);

  sf::CircleShape createVertexShape(const Vector& position, const float radius,
    const sf::Color color = sf::Color::Red, const sf::Color borderColor = sf::Color::White);

  std::vector<sf::CircleShape> createVerticesShapes(const std::vector<Vector>& positions, 
    const float radius = 15.0f, sf::Color color = sf::Color::Red, const sf::Color borderColor = sf::Color::White);

  std::vector<sf::VertexArray> createEdgesShapes(const std::vector<Graph::Edge> & edges, 
    const std::vector<Vector> & verticesPositions, float vertexRadius = 0);

  bool addVertexShape(sf::RenderWindow& window, sf::Vector2u windowSize, Graph& graph,
    std::vector<sf::CircleShape>& vertices, float radius = 10.0f, sf::Color color = sf::Color::Blue);

  /*
  Graph::Vertex selectVertex(sf::RenderWindow& window, const std::vector<Vector>& verticesPositions,
    float vertexRadius);
  */

  void drawVertices(sf::RenderWindow& window, const std::vector<sf::CircleShape>& vertices);
  void drawEdges(sf::RenderWindow& window, const std::vector<sf::VertexArray>& edges);
  void drawGraph(sf::RenderWindow& window, const std::vector<sf::CircleShape>& vertices,
    const std::vector<sf::VertexArray>& edges);
}
