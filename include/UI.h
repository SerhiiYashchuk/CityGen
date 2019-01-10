#include <SFML/Graphics.hpp>

namespace CityGen
{
	constexpr float uiBlockWidth = 250.0f;
	constexpr float uiBlockPadding = 5.0f;

	constexpr float zoomAmount = 1.1f;

	void zoomViewAt(sf::RenderWindow& window, sf::Vector2i pixel, float zoom);
}
