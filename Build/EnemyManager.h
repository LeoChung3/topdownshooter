#pragma once
#include "Enemy.h"

class EnemyManager 
{
private:
	bool gameopen = false;

	int NumOfEnemies = 1;
	vector<Enemy> Enemies;


	int Killed = 0;
	//int NumOfEnemies = sizeof(Enemies);


public:
	void move(sf::Vector2f playerPos, sf::FloatRect playerRect, float dt);
	void draw(sf::RenderWindow* window);
	Enemy returnEnemyNum(int i);
	int getNumOfEnemies();
	sf::Sprite getSprite(int a);

	void KillEnemy(int a, bool killed, sf::Vector2f playerPos, sf::Vector2f windowSize, int mapSize, int imageSize);

	int getKills();

	void restart();

	void changeopen(bool a)
	{
		gameopen = a;
		cout << gameopen << endl;
	}
	void sayhello(int a)
	{
		while (gameopen)
		{
					cout << "aaaaaa" << a << endl;

		}
		if (!gameopen)
		{
			cout << "gamenotopen" << endl;
		}
	}
	EnemyManager(int mapSize, int imageSize, int a, float speed)
	{
		int mappixels = mapSize * imageSize;

		NumOfEnemies = a;
		for (int i = 0; i < a; i++) {
			Enemies.push_back(Enemy());
			Enemies[i].setSpritepos((rand() % (mappixels * 2)) - mappixels, (rand() % (mappixels * 2)) - mappixels);

			Enemies[i].loadTexture();
			Enemies[i].setAlive();
			Enemies[i].checkAlive();
			Enemies[i].setSpeed(speed);
		}
	}


};