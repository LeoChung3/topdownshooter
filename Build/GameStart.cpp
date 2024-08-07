#include "GameStart.h"

int GameStart::update(sf::RenderWindow& window)
{
	leaderboard.LoadScore();

	sf::RenderWindow* windowPtr = &window;

	// 0 - mainmenu
	// 1 - maingame

	Pov.setSize(1920.f, 1090.f);
	Pov.setCenter(0, 0); // sets the centre of the pov to 0,0, so it is in the centre of the entire map


	Player player(100, 0.f, 1.f, 5.f);
	Player* playerPtr = &player;
	Weapon gun(30, 25.f); // bulletammount, magazine, speed
	//UI userInterface;
	TileMap map(20,64,1.f);
	Scenery scenery(map.getMapSize(), map.getImageSize());
	EnemyManager enemyManager(map.getMapSize(), map.getImageSize(), 10, 5.f);

	Collectable collectables(map.getMapSize(),map.getImageSize(), 7);

	MaterialManager matManager(map.getMapSize(), map.getImageSize());
	MaterialManager* matManagerPtr = &matManager;

	GameObject& gameObjectPlayer = player;

	shelter shelter(matManagerPtr);
	MiniGun minigun(matManagerPtr);

	sf::Event event;
	while (window.isOpen())
	{
		switch (switchStatements)
		{

		case 0:
			window.clear();
			userInterface.mainMenu(window);
			window.display();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				switchStatements = 1;
			}
			break;

		case 1:
			mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

			if (pauseClock.getElapsedTime().asSeconds() >= 0.25f)
			{
				if (player.gethealth() > 0)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
					{
						if (!leaderBoardOpen)
						{
							gameRunning = !gameRunning;
							inventoryOpen = !inventoryOpen;
							pauseClock.restart();
							minigun.craftItem();
						}
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
					{
						if (!inventoryOpen)
						{
							leaderboard.LoadScore();
							gameRunning = !gameRunning;
							leaderBoardOpen = !leaderBoardOpen;
							pauseClock.restart();
						}
					}
				}
			}
			float dt = clock.getElapsedTime().asSeconds() >= 1.0f / f_FPS;
			//Wait until 1/60th of a second has passed, then update everything.
			if (dt)
			{
				b_redraw = true; //We're ready to redraw everything
				clock.restart();
			}

			//if player health is below 0, game ends and closes window
			if (player.gethealth() <= 0)
			{
				gameRunning = false;
			}

			//Poll an event on the SFML window. Only really need to know about closure. 
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}

			}

			if (gameRunning)
			{
				//player function that moves, rotates, and shoots the gun
				player.PlayerInput(gun, windowPtr, PovPtr, povSpeed, mousePos, dt, map.getMapSize(), map.getImageSize(), matManager, leaderboard);

				//enemy manager moves all enemies towards player
				enemyManager.move(gameObjectPlayer.getSprite().getPosition(), gameObjectPlayer.getSprite().getGlobalBounds(), dt); // upcasting used to get sprite position and global bounds of player sprite

				//checks if the gun is picked up, if its not but the player collides, gun is picked up
				if (!gun.getPickedUp()) {
					gun.pickup(player.getSprite().getGlobalBounds());
					if (gun.getPickedUp()) {
						player.setGunTexture();
					}
				}
				//moves all active bullets towards their direction
				gun.move(window, dt);

				//enemy shoot at player

				// player collision with enemy
				for (int i = 0; i < enemyManager.getNumOfEnemies(); i++) {
					player.collisions(enemyManager.getSprite(i).getGlobalBounds());
				}

				//bullet collisions with enemy
				for (int i = 0; i < enemyManager.getNumOfEnemies(); i++) {
					enemyManager.KillEnemy(i, gun.guncollisions(enemyManager.getSprite(i)), player.getSprite().getPosition(), Pov.getSize(), map.getMapSize(), map.getImageSize());
				}

				//player collision with items
				player.getMedkit(collectables.collided(gameObjectPlayer.getSprite())); // upcasting used, to get sprite of player through game object class, 


				matManager.Collision(player.getSprite().getGlobalBounds());
				//sets UI variables
				userInterface.setHealthText(player.gethealth());
				userInterface.setAmmoText(gun.returnMagazine(), gun.returnmagazinesize());
				userInterface.setKillText(enemyManager.getKills());
			}

			//Draw to the window.
			if (b_redraw)
			{
				b_redraw = false;
				window.clear();

				window.setView(Pov); // sets the view to the pov

				map.drawMap(window, PovPtr); // draws tilemap

				scenery.drawScenery(map.getMapSize(), map.getImageSize(), window);

				player.draw(window); // draws player

				enemyManager.draw(windowPtr); // draws enemies

				gun.draw(window); // draws bullets

				collectables.draw(window); // draws collectable items

				matManager.draw(window); // draws all the materials on the ground

				window.setView(window.getDefaultView()); // sets the view to default so it can draw ui normally

				userInterface.draw(window); // draws ui

				if (inventoryOpen)
				{
					userInterface.drawInventory(window, matManager, mousePos, minigun);
				}
				if (leaderBoardOpen)
				{
					leaderboard.showLeaderBoard(window);
				}
				if (player.gethealth() <= 0)
				{
					userInterface.deathScreen(window, event);

					if (userInterface.nameGiven == true)
					{
						leaderboard.NewScore(userInterface.name, enemyManager.getKills());
						player.restart();
						enemyManager.restart();
						leaderboard.LoadScore();
						gameRunning = true;
						userInterface.nameGiven = false;
						userInterface.name = "";
						switchStatements = 0;
					}
				}


				window.display();

			}
			break;
		}
	}
	return 0;

}

int GameStart::getrandomnum()
{
	return 100;
}
