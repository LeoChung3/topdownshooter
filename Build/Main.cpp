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

#include "CSVreader.h"

#include "MyThreading.h"

#include <mutex>
//credits
// gun sprite https://bigmack.itch.io/wwii-mega-gun-pack?download

//help with threading
// https://www.geeksforgeeks.org/multithreading-in-cpp/
//to do list
//make items be craftable
//make item be added to inventory
//medkit be added to inventory
//

int main()
{

	bool gamestarted = false;

	// 0 - mainmenu
	// 1 - maingame
	int switchStatements = 0;
	bool gameRunning = true;
	bool inventoryOpen = false;
	bool leaderBoardOpen = false;
	bool b_invOpen = true;
	sf::RenderWindow window(sf::VideoMode(1920, 1080, 32), "Game Demo", sf::Style::Default); //Draw an SFML window.
	sf::RenderWindow* windowPtr = &window;

	sf::View Pov; // pov window
	sf::View* PovPtr = &Pov;
	Pov.setSize(1920.f, 1090.f);
	Pov.setCenter(0, 0); // sets the centre of the pov to 0,0, so it is in the centre of the entire map

	sf::Vector2f mousePos;
	float povSpeed = 10.f;

	Player player(100, 0.f, 1.f, 5.f);
	Player* playerPtr = &player;
	UI userInterface;
	TileMap map(20, 64, 1.f);
	Scenery scenery(map.getMapSize(), map.getImageSize());
	EnemyManager enemyManager(map.getMapSize(), map.getImageSize(), 10, 5.f);

	Collectable collectables(map.getMapSize(), map.getImageSize(), 7);

	MaterialManager matManager(map.getMapSize(), map.getImageSize());
	MaterialManager* matManagerPtr = &matManager;
	LeaderBoard leaderboard;
	leaderboard.LoadScore();

	GameObject& gameObjectPlayer = player;

	shelter shelter(matManagerPtr);
	MiniGun minigun(matManagerPtr);
	Weapon gun(0, 25.f, &minigun); // bulletammount, magazine, speed

	//Setting the fps. This can dictate the movement / redraw speed.
	const float f_FPS = 60.0f; //The desired FPS. (The number of updates each second).
	bool b_redraw = true;      //Redraw everything on the screen.

	//Clock to get the time.
	sf::Clock clock;
	sf::Clock pauseClock;
	sf::Clock runtime;
	//Check if the window is open or closed.
	sf::Event event;

	bool ispressed = false;

	CSVreader csvfilestuff;
	MyThreading mythreads(&gameRunning, &clock);

	window.setActive(false);



	//1. Load multiple images for a level and display them.
	// thread to draw all elements of the game to the window, seperate from the main thread
	//3. Create a simple start up splash screen(a section of the
	//	screen) that can be displayed and interacted with whilst the
	//	above actions are carried out.A button should be able to be
	//	clicked on by the mouse and change colour when it does so.
	// part of the drawing is the splash menu, which is changed through the switch statements after 5 seconds, it will .get() and close the thread switching to the main menu
	thread th1(&MyThreading::DrawEverything, &mythreads, windowPtr, &inventoryOpen, &leaderBoardOpen, &player,&enemyManager, &Pov, &map,
											 &gun, &collectables, &matManager, &userInterface, &minigun, &leaderboard, &event, &switchStatements);

	//2. Read the file provided in the GitHub repository into a suitable container.
	// thread to real all elements from the csv file and loads it in to a vector
	//unused
	//thread th2(&CSVreader::readfile, &csvfilestuff, "../Assets/UserDetails.csv"); 


	//	5. Use of async and futures to read the file provided in the GitHub repository into a suitable container
	// thread uses async and future to run the function along side other threads, and lodas the data in to a vector
	std::future<int> th5 = std::async(std::launch::async, &CSVreader::readfile2, &csvfilestuff, "../Assets/UserDetails.csv");


	// thread to move all the positions of the enemies seperate from the mainloop
	thread th6(&MyThreading::moveEverything, &mythreads, windowPtr, &enemyManager, &player);

	//assignment 3
	/*moved the drawing to a thread and the movement of the enemies to a thread
	can read a csv file and check if its finished and if it is, moves ot the main menu*/
	while (window.isOpen())
	{
		switch (switchStatements)
		{

		case 0:
			gameRunning = false;
			
			//std::this_thread::sleep_for(std::chrono::seconds(5));
			while (runtime.getElapsedTime().asSeconds() <= 5.f)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (!ispressed)
					{
						ispressed = true;
						mythreads.colour += 1;

						if (mythreads.colour >= 4)
						{

							mythreads.colour = 0; // changes the colour of the square in the splash screen

						}
					}
				}
				else
				{
					ispressed = false;
				}
				
			}
			if (th5.get() == 1) // checks if the csv file was fully loaded before it goes to the main menu section
			{
				switchStatements = 1;
			}
			break;

		case 1:
			gameRunning = false;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				switchStatements = 2;
			}
			break;
		case 2:
			mythreads.run = true;
			gameRunning = true;

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
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
					{
						matManager.cheat();
					}
				}
			}

			float dt = clock.getElapsedTime().asSeconds() >= 1.0f / f_FPS;
			//Wait until 1/60th of a second has passed, then update everything.
			if (dt)
			{
				mythreads.b_redraw = true;
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

			if (gameRunning == true)
			{
				window.setActive(false);
				mythreads.dt = dt;

				//player function that moves, rotates, and shoots the gun
				player.PlayerInput(gun, PovPtr, povSpeed, mousePos, dt, map.getMapSize(), map.getImageSize(), matManager, leaderboard);

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
				b_redraw = false; //We're ready to redraw everything
				mythreads.b_redraw = false;

			}
			break;
		}
	}
	th1.join();
	//th2.join();
	th6.join();



	return 0;
}