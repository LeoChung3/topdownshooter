#pragma once
#include "Initialise.h"

#include "Player.h"
#include "Weapon.h"
#include "EnemyManager.h"
#include "Collectable.h"
#include "UI.h"
#include "TileMap.h"
#include "Scenery.h"
#include "MaterialManager.h"
#include "CraftingMaterial.h"
#include "LeaderBoard.h"
#include "Shelter.h"
#include "MiniGun.h"
#include <sstream>

#include "GameObject.h"
#include "Bullet.h"
#include "Enemy.h"

class GameStart
{
private:
	int switchStatements = 0;
	bool gameRunning = true;
	bool inventoryOpen = false;
	bool leaderBoardOpen = false;
	bool b_invOpen = true;

	sf::View Pov; // pov window
	sf::View* PovPtr = &Pov;

	sf::Vector2f mousePos;
	float povSpeed = 10.f;


	UI userInterface;

	LeaderBoard leaderboard;

	bool b_redraw = true;
	const float f_FPS = 60.0f;

	sf::Clock clock;
	sf::Clock pauseClock;

public:
	GameStart()
	{
	}

	int update(sf::RenderWindow& window);
	int getrandomnum();
};