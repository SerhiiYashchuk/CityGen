#include <iostream>

#include <imgui.h>
#include <sfml-imgui/imgui-SFML.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "GraphVisualization.h"
#include "UI.h"

int main(int /*argc*/, char const * /*argv[]*/)
{
  sf::ContextSettings settings;
  settings.antialiasingLevel = 4;

  sf::Vector2u windowSize = { 1366, 768 };

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML Graph implementation", sf::Style::Default, settings);
  window.setActive(true);

  sf::View view;
  view.setCenter(sf::Vector2f(0.0f, 0.0f));
  view.setSize(windowSize.x, windowSize.y);

  window.setView(view);

  ImGui::SFML::Init(window);

  bool isRunning = true;

  CityGen::Graph graph;

  graph.addVertex({ 20.0f, 20.0f });
  graph.addVertex({ -100.0f, 0.0f });
  graph.addVertex({ -400.0f, -200.0f });
  graph.addVertex({ 300.0f, -300.0f });
  graph.addVertex({ -400.0f, -450.0f });
  graph.addVertex({ 300.0f, 100.0f });
  
  graph.addEdge(0, 1);
  graph.addEdge(1, 2);
  graph.addEdge(2, 0);
  graph.addEdge(0, 4);
  graph.addEdge(0, 3);
  graph.addEdge(3, 5);

  const float graphVertexRadius = 20.0f;
  const sf::Color graphVertexColor = sf::Color::Blue;

  float newVertexRadius = 10.0f;

  std::vector<CityGen::Vector> verticesPositions = getVerticesPositions(graph);
  std::vector<CityGen::Graph::Edge> edgesIdices = graph.getEdges();

  std::vector<sf::CircleShape> vertices = CityGen::createVertices(verticesPositions, graphVertexColor, graphVertexRadius);
  std::vector<sf::VertexArray> edges = CityGen::createEdges(edgesIdices, verticesPositions, graphVertexRadius);
  
  sf::Clock deltaClock;

  bool isAddingNodesMode = false;

  while (isRunning)
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      ImGui::SFML::ProcessEvent(event);

      switch (event.type)
      {
      case sf::Event::Closed:
      {
        isRunning = false;
      }  
      break;

      case sf::Event::Resized:
      {
        windowSize = window.getSize();

        sf::FloatRect resizedArea(-(event.size.width / 2.0f), -(event.size.height / 2.0f), event.size.width, event.size.height);
        window.setView(sf::View(resizedArea));

        std::cout << " - Window has been resised -> (" << windowSize.x << ", " << windowSize.y << ")" << std::endl;
      }
        break;

      case sf::Event::MouseButtonPressed:
      {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
          if (isAddingNodesMode && sf::Mouse::getPosition(window).x < windowSize.x - CityGen::uiBlockWidth)
          {
            sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(window);
            sf::Vector2f mousePositionInCoords = window.mapPixelToCoords(mousePositionInWindow);

            CityGen::Graph::Vertex vertexIndex = graph.addVertex({ mousePositionInCoords.x,  mousePositionInCoords.y });

            CityGen::Vector vertexPosition = CityGen::getVertexPosition(graph, vertexIndex);
            sf::CircleShape vertex = CityGen::createVertex(vertexPosition, graphVertexColor, newVertexRadius);
            vertices.push_back(vertex);

            std::cout << "vertex coord: (" << vertexPosition.x << ", " << vertexPosition.y << ")" << std::endl;
        }
      }
      break;

      case sf::Event::MouseWheelScrolled:
      {
        if (event.mouseWheelScroll.delta > 0)
          CityGen::zoomViewAt(window, { event.mouseWheelScroll.x, event.mouseWheelScroll.y }, (1.f / CityGen::zoomAmount));
        else if (event.mouseWheelScroll.delta < 0)
          CityGen::zoomViewAt(window, { event.mouseWheelScroll.x, event.mouseWheelScroll.y }, CityGen::zoomAmount);
      }
        break;
      };
    
      ImGui::SFML::Update(window, deltaClock.restart());

      window.clear();

      ImGui::Begin("ui");

      ImGui::SetWindowPos({ windowSize.x - CityGen::uiBlockWidth - CityGen::uiBlockPadding, CityGen::uiBlockPadding });
      ImGui::SetWindowSize({ static_cast<float>(CityGen::uiBlockWidth), 0.0f });

      if (ImGui::Button("new node"))
      {
        isAddingNodesMode = isAddingNodesMode ? false : true;
      }

      ImGui::SliderFloat("node radius", &newVertexRadius, 1.0f, 50.0f);

      ImGui::End();

      CityGen::drawEdges(window, edges);
      CityGen::drawVertices(window, vertices);

      ImGui::SFML::Render(window);

      window.display();
    }
  }

  return 0;
}
