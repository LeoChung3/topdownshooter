#include "Tile.h"

void Tile::setLocation(float a, float b)
{
	sprite.setPosition(a,b);
}

void Tile::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
