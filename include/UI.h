#include <SFML/Graphics.hpp>

namespace CityGen
{
  enum UIMode { Select, Add };

  constexpr float uiBlockWidth = 250.0f;
  constexpr float uiBlockPadding = 5.0f;

  constexpr float zoomAmount = 1.1f;
  constexpr float moveAmount = 20.0f;

  void zoomViewAt(sf::RenderWindow& window, sf::Vector2i pixel, float zoom);
  void moveViewTo(sf::RenderWindow& window, const sf::Vector2f displacement);
}
