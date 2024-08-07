#pragma once
#include "Initialise.h"
#include "Player.h"
#include "EnemyManager.h"
#include "TileMap.h"
#include "Weapon.h"
#include "Collectable.h"
#include "MaterialManager.h"
#include "UI.h"
#include "MiniGun.h"
#include "LeaderBoard.h"
using namespace std;

//1. Load multiple images for a level and display them.
// done
//2. Read the file provided in the GitHub repository into a suitable
//container.
// done 
//3. Create a simple start up splash screen(a section of the
//	screen) that can be displayed and interacted with whilst the
//	above actions are carried out.A button should be able to be
//	clicked on by the mouse and change colour when it does so.
// done
// 
// 
// 
//	4. Use mutexs to manage data so that the images are only
//	displayed on the screen when the file has been loaded.
//	5. Use of async and futures to read the file provided in the
//	GitHub repository into a suitable container

class MyThreading
{
private:
public:
	std::mutex mymutex;
	sf::Clock* Clock;
	bool run = false;
	bool b_redraw = false;
	bool* gamerunning;
	sf::Vector2f mousePos;
	float dt = 1.f;

	int colour = 0;

	MyThreading(bool* Gamerunning, sf::Clock* clock)
	{
		Clock = clock;
		gamerunning = Gamerunning;
	};

	void DrawEverything(sf::RenderWindow* window, bool* inventoryOpen, bool* leaderBoardOpen, Player* player, 
						EnemyManager* enemymanager, sf::View* Pov,TileMap* map, Weapon* gun, Collectable* collectables,
						MaterialManager* matmanager, UI* userinterface, MiniGun* minigun, LeaderBoard* leaderboard, 
						sf::Event* event, int* switchstatement)
	{
		sf::View &a = *Pov;
		sf::RenderWindow& b = *window;
		player->window = window;
		while (window->isOpen())
		{
			std::lock_guard<std::mutex> lock(mymutex);

			switch (*switchstatement)
			{
			case 0:
				window->clear();
				userinterface->SplashScreen(*window, colour);
				window->display();
				break;

			case 1:
				window->clear();
				userinterface->mainMenu(*window);
				window->display();
				break;
			case 2:
			{
				if (b_redraw)
				{
					player->SetRotation((atan2(mousePos.y - window->getSize().y / 2, mousePos.x - window->getSize().x / 2.f) / (3.141 / 180.f)));
					player->playercamera = Pov;
					window->clear();
					window->setView(a); // sets the view to the pov

					map->drawMap(window, Pov);

					player->draw(window);
					enemymanager->draw(window);
					gun->draw(b);
					collectables->draw(b);
					matmanager->draw(b);


					window->setView(window->getDefaultView());
					userinterface->draw(b);
					userinterface->hotBar(b, *minigun, *gun);


					if (*leaderBoardOpen)
					{
						leaderboard->showLeaderBoard(*window);

					}
					if (*inventoryOpen)
					{
						//	userInterface.drawInventory(window, matManager, mousePos, minigun);
						userinterface->drawInventory(*window, *matmanager, mousePos, *minigun);

					}

					if (player->gethealth() <= 0)
					{
						*gamerunning = false;
						userinterface->deathScreen(*window, *event);

						if (userinterface->nameGiven == true)
						{
							leaderboard->NewScore(userinterface->name, enemymanager->getKills());
							player->restart();
							enemymanager->restart();
							leaderboard->LoadScore();
							*gamerunning = true;
							userinterface->nameGiven = false;
							userinterface->name = "";
							*switchstatement = 1;
						}
					}
					window->display();

					mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(b));
					player->MousePos = mousePos;

				}
				break;
			}
			}
		}

	}

	void moveEverything(sf::RenderWindow* window, EnemyManager* enemymanager, Player* player)
	{
		while (window->isOpen())
		{
			//std::lock_guard<std::mutex> lock(mymutex);
			if (run)
			{
				enemymanager->move(player->getSprite().getPosition(), player->getSprite().getGlobalBounds(), dt); // upcasting used to get sprite position and global bounds of player sprite
				run = false;
			}


		}
	}

};