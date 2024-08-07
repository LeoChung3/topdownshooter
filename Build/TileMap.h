#pragma once
#include "GameObject.h"
#include "Tile.h"
class TileMap
{
private:

public:
	sf::Texture SpriteSheet;
	int map[100][100];
	int mapSize = 20;
	int imageSize = 0;
	float scaling = 1.f;
	TileMap(int mapsize, int imagesize, float scale)
	{
		mapSize = mapsize;
		imageSize = imagesize;
		scaling = scale;
		if (!SpriteSheet.loadFromFile("../Assets/topdown/Tilesheet/tilesheet_complete.png"))
		{
			cout << "cant load sprite sheet" << endl;
		}

		for (int i = -mapSize; i < mapSize; i++)
		{
			for (int i2 = -mapSize; i2 < mapSize; i2++)
			{
				map[i + mapSize][i2 + mapSize] = rand() % 3;
			}
		}
	}
	int getTile();
	void drawMap(sf::RenderWindow*, sf::View* camera);
	int getMapSize();
	int getImageSize();

};