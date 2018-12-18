#include <Hyperstreamline/Tracing/Graph.h>
#include <SFML/Graphics.hpp>

namespace CityGen 
{
  std::vector<Vector> getVerticesPositions(const Graph & graph);

  std::vector<sf::CircleShape> createVertices(const std::vector<Vector> & verticesPositions,
    sf::Color color = sf::Color::Red, float vertexSize = 15.0f);

  std::vector<sf::VertexArray> createEdges(const std::vector<Graph::Edge> & edges, 
    const std::vector<Vector> & verticesPositions, float vertexRadius = 0);

  void drawVertices(sf::RenderWindow& window, std::vector<sf::CircleShape> vertices);

  void drawEdges(sf::RenderWindow& window, std::vector<sf::VertexArray> edges);
}
