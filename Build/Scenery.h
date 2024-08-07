#pragma once
#include "GameObject.h"
class Scenery : GameObject
{
private:

	sf::Texture SpriteSheet;
	sf::Vector2f treePos[10];
public:
	Scenery(int mapSize, int imagesize)
	{
		int mappixels = mapSize * imagesize;

		if (!SpriteSheet.loadFromFile("../Assets/topdown/Tilesheet/tilesheet_complete.png"))
		{
			cout << "cant load sprite sheet" << endl;
		}

		sprite.setTexture(SpriteSheet);

		for (int i = 0; i < 10; i++)
		{
			treePos[i] = sf::Vector2f((rand() % (mappixels * 2)) - mappixels, (rand() % (mappixels * 2)) - mappixels);
		}
	}
	
	void drawScenery(float mapsize, float imagesize, sf::RenderWindow&);

};