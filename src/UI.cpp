#include "UI.h"

namespace CityGen
{
	void zoomViewAt(sf::RenderWindow& window, sf::Vector2i pixel, float zoom)
	{
		const sf::Vector2f beforeCoord(window.mapPixelToCoords(pixel));

		sf::View view(window.getView());
		view.zoom(zoom);

		window.setView(view);

		const sf::Vector2f afterCoord(window.mapPixelToCoords(pixel));
		const sf::Vector2f offsetCoords(beforeCoord - afterCoord);

		view.move(offsetCoords);
		window.setView(view);
	}
}