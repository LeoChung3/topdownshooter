#pragma once
#include "GameObject.h"

class Tile: public GameObject
{
private:
	sf::Vector2i Location;
public:

	Tile() = default;
	void setLocation(float a, float b);
	void draw(sf::RenderWindow&);
};