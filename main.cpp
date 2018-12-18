#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

#include <graphVisualization.h>

int main(int /*argc*/, char const * /*argv[]*/)
{
  sf::ContextSettings settings;
  settings.antialiasingLevel = 4;

  sf::RenderWindow window(sf::VideoMode(1366, 768), "SFML Graph implementation", sf::Style::Default, settings);
  window.setActive(true);

  bool isRunning = true;

  CityGen::Graph graph;

  graph.addVertex({ 500.0f, 100.0f });
  graph.addVertex({ 400.0f, 500.0f });
  graph.addVertex({ 100.0f, 300.0f });
  graph.addVertex({ 800.0f, 200.0f });
  graph.addVertex({ 100.0f, 100.0f });
  graph.addVertex({ 800.0f, 600.0f });
  
  graph.addEdge(0, 1);
  graph.addEdge(1, 2);
  graph.addEdge(2, 0);
  graph.addEdge(0, 4);
  graph.addEdge(0, 3);
  graph.addEdge(3, 5);

  const float vertexRadius = 20.0f;

  std::vector<CityGen::Vector> verticesPositions = getVerticesPositions(graph);
  std::vector<CityGen::Graph::Edge> edgesIdices = graph.getEdges();

  std::vector<sf::CircleShape> vertices = CityGen::createVertices(verticesPositions, sf::Color::Red, vertexRadius);
  std::vector<sf::VertexArray> edges = CityGen::createEdges(edgesIdices, verticesPositions, vertexRadius);
  
  while (isRunning)
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        isRunning = false;
      }

      if (event.type == sf::Event::Resized)
      {
        glViewport(0, 0, event.size.width, event.size.height);
        std::cout << " - Window has been resised -> (" << window.getSize().x << ", " << window.getSize().y <<")" << std::endl;
      }

      window.clear();

      CityGen::drawEdges(window, edges);
      CityGen::drawVertices(window, vertices);
      
      window.display();
    }
  }

  return 0;
}
