#include <Hyperstreamline/Tracing/Graph.h>
#include <SFML/Graphics.hpp>

namespace CityGen 
{
  std::vector<CityGen::Vector> getVerticesPositions(const CityGen::Graph & graph);

  std::vector<sf::CircleShape> createVertices(const CityGen::Graph & graph,
    sf::Color color = sf::Color::Red, float vertexSize = 15.0f);

  std::vector<sf::VertexArray> getEdgesPositions(const CityGen::Graph & graph, float vertexRadius = 0);

  void drawVertices(sf::RenderWindow& window, std::vector<sf::CircleShape> vertices);

  void drawEdges(sf::RenderWindow& window, std::vector<sf::VertexArray> edges);
}