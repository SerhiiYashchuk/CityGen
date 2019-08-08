#include <imgui.h>
#include <sfml-imgui/imgui-SFML.hpp>

#include <SFML/Graphics.hpp>

#include "UI.h"
#include "graphVisualization.h"

namespace CityGen {
  class Program
  {
  public:
    Program(const sf::Vector2u windowSize, const std::string windowName) :
      _settings(),
      _windowSize(windowSize),
      _window(sf::VideoMode(windowSize.x, windowSize.y), windowName, sf::Style::Default),
      _view()
    {
      _uimode = UIMode::Select;
    }

    void run()
    {
      _window.setActive(true);

      _view.setCenter(sf::Vector2f(0.0f, 0.0f));
      _view.setSize(static_cast<float>(_windowSize.x), static_cast<float>(_windowSize.y));

      _window.setView(_view);

      ImGui::SFML::Init(_window);

      // some Graph stuff
      Graph graph;

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

      float vertexRadius = 20.0f;
      const sf::Color vertexColor = sf::Color::Blue;

      std::vector<Vector> verticesPositions = getVerticesPositions(graph);
      std::vector<Graph::Edge> edgesIndices = graph.getEdges();

      std::vector<sf::CircleShape> vertices = createVerticesShapes(verticesPositions, vertexRadius, vertexColor);
      std::vector<sf::VertexArray> edges = createEdgesShapes(edgesIndices, verticesPositions, vertexRadius);

      while (_window.isOpen())
      {
        processEvents(graph, vertices, vertexRadius, vertexColor);
        update();
        render(vertices, edges, vertexRadius);
      }
    }

  private:
    // User Input
    void processEvents(Graph& graph, std::vector<sf::CircleShape>& vertices, 
      float vertexRadius, sf::Color vertexColor)
    {
      sf::Event event;

      while (_window.pollEvent(event))
      {
        ImGui::SFML::ProcessEvent(event);

        switch (event.type)
        {
        case sf::Event::Closed:
        {
          _window.close();
        }
        break;

        case sf::Event::Resized:
        {
          _windowSize = _window.getSize();

          sf::FloatRect resizedArea(-(event.size.width / 2.0f), -(event.size.height / 2.0f), 
		    static_cast<float>(event.size.width), static_cast<float>(event.size.height));
          _window.setView(sf::View(resizedArea));

          std::cout << " - Window has been resised -> (" << _windowSize.x << ", " << _windowSize.y << ")" << std::endl;
        }
        break;

        case sf::Event::MouseButtonPressed:
        {
          if (event.mouseButton.button == sf::Mouse::Left)
          {
            switch (_uimode)
            {
            case UIMode::Select:
            {
              // TODO: function that selectes vertex/edge from graph by sf::Mouse::getPosition(window) 

              // Graph::Vertex selectedVertex = selectVertex(window, verticesPositions, vertexRadius);
            }
            break;

            case UIMode::Add:
            {
              // TODO: Logic to choose graph in which need to add vertices
              addVertexShape(_window, _windowSize, graph, vertices, vertexRadius, vertexColor);
            }
            break;

            };
          }
        }
        break;

        case sf::Event::MouseWheelScrolled:
        {
          if (event.mouseWheelScroll.delta > 0)
            zoomViewAt(_window, { event.mouseWheelScroll.x, event.mouseWheelScroll.y }, (1.0f / zoomAmount));
          else if (event.mouseWheelScroll.delta < 0)
            zoomViewAt(_window, { event.mouseWheelScroll.x, event.mouseWheelScroll.y }, zoomAmount);
        }
        break;

        case sf::Event::KeyPressed:
        {
          switch (event.key.code)
          {
          case sf::Keyboard::Left:
            moveViewTo(_window, sf::Vector2f(-moveAmount, 0.0f));
            break;
          case sf::Keyboard::Right:
            moveViewTo(_window, sf::Vector2f(moveAmount, 0.0f));
            break;
          case sf::Keyboard::Up:
            moveViewTo(_window, sf::Vector2f(0.0f, -moveAmount));
            break;
          case sf::Keyboard::Down:
            moveViewTo(_window, sf::Vector2f(0.0f, moveAmount));
            break;
          };
        }
        break;

        };
      }
    }

    // Logic
    void update()
    {
    }

    // Render image
    void render(std::vector<sf::CircleShape>& vertices, std::vector<sf::VertexArray>& edges, 
      float vertexRadius)
    {
      ImGui::SFML::Update(_window, _deltaClock.restart());

      _window.clear();

      ImGui::Begin("ui");

      ImGui::SetWindowPos({ _windowSize.x - uiBlockWidth - uiBlockPadding, uiBlockPadding });
      ImGui::SetWindowSize({ static_cast<float>(uiBlockWidth), 0.0f });

      if (ImGui::Button("select element"))
      {
        _uimode = UIMode::Select;
      }

      if (ImGui::Button("add new vertex"))
      {
        _uimode = UIMode::Add;
      }

      ImGui::SliderFloat("vertex radius", &vertexRadius, 1.0f, 50.0f);

      ImGui::End();

      drawEdges(_window, edges);
      drawVertices(_window, vertices);

      ImGui::SFML::Render(_window);

      _window.display();
    }

  private:
    sf::ContextSettings _settings;
    sf::RenderWindow _window;
    sf::View _view;
    sf::Clock _deltaClock;

    UIMode _uimode;
    sf::Vector2u _windowSize;
  };
}
