#pragma once
#include "GameObject.h"

class Potion: public GameObject
{
private:
public:

	bool pickedUp = false;
	void setPosition(sf::Vector2f pos);

	Potion()
	{
		if (!texture.loadFromFile("../Assets/topdown/Tilesheet/spritesheet.png")) {
			std::cout << "Error loading the image!" << std::endl;
		}
		sprite.setTexture(texture);
		sprite.setPosition(-1000.f,-1000.f);
	}
	~Potion()
	{
		cout << "health kit collected" << endl;
	}
};