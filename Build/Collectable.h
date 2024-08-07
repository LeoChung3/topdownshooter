#pragma once

#include "GameObject.h"

#include "Potion.h"

class Collectable : public GameObject
{
private:
	Potion healthKit;
	int healthPickUps;
	//Potion healthItem[7];
	std::vector <Potion> Healthkits;

public:
	bool collided(sf::Sprite player);
	void draw(sf::RenderWindow& window);
	void setPos(int a, sf::Vector2f Pos);
	Collectable(int mapSize, int imageSize, int a)
	{

		int mappixels = mapSize * imageSize;
		healthPickUps = a;
		for (int i = 0; i < healthPickUps; i++) 
		{
			Healthkits.push_back(healthKit);
			Healthkits[i].setPosition(sf::Vector2f((rand() % (mappixels * 2)) - mappixels, (rand() % (mappixels * 2)) - mappixels));

		}
		/*for (int i = 0; i < healthPickUps; i++) {
			healthItem[i].setPosition(sf::Vector2f((rand() % (mappixels * 2)) - mappixels, (rand() % (mappixels * 2)) - mappixels));

		}*/
	}
	Collectable() 
	{
		healthPickUps = 5;
	}
};