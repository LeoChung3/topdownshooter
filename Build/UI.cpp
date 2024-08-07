#include "UI.h"

//sets health text
void UI::setHealthText(int health)
{
	string healthText = "Health: " + to_string(health);
	Health.setString(healthText);

}

//sets ammo text
void UI::setAmmoText(int ammo, int size)
{
	string ammoText = to_string(ammo) + "/" + to_string(size);
	Ammo.setString(ammoText);

}

//sets kill text
void UI::setKillText(int kills)
{
	string killText = "Kills : " + to_string(kills);
	KillCount.setString(killText);
}

//draws all the ui texts
void UI::draw(sf::RenderWindow& window)
{
	window.draw(Health);
	window.draw(Ammo);
	window.draw(KillCount);
}

void UI::drawInventory(sf::RenderWindow& window, MaterialManager& matManager, sf::Vector2f mousePos, MiniGun& minigun)
{
	float scale = 1.3f;
	int gridsize = 4;
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(600.f,330.f));
	shape.setPosition((1920.f/2) - (64 * scale * gridsize / 2), (1080.f/2) - (64 * scale * gridsize / 2));
	shape.setFillColor(sf::Color::White);
	window.draw(shape);
	sf::Sprite tile;
	tile.setTexture(inventoryslot);
	tile.setTextureRect(sf::IntRect((15 * 64), (13 * 64), 64, 64));
	tile.setScale(scale, scale);
	for (int i = 0; i < 4; i++) {
		for (int i2 = 0; i2 < 4; i2++) {
			tile.setPosition(sf::Vector2f((1920.f / 2.f) - (64 * scale * gridsize/2) + (i * 64 * scale), (1080.f / 2.f) - ((64 * scale * gridsize/2) - (i2 * 64 * scale))));
						window.draw(tile);
		}
		
	}
	
	matManager.printInventory(window, mousePos);

	shape.setSize(sf::Vector2f(30, 30));
	shape.setPosition((1920.f / 2) + (64 * 1.3 * 2), (1080.f / 2) + (330 / 2) - 30);
	shape.setFillColor(sf::Color::Red);
	if (shape.getGlobalBounds().contains(mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			cout << "make minigun" << endl;
			shape.setFillColor(sf::Color::Green);
			minigun.craftItem();


		}
	}
	window.draw(shape);

}
void UI::deathScreen(sf::RenderWindow& window, sf::Event event)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(500.f, 500.f));
	shape.setPosition((1920.f / 2) - 250, (1080.f / 2) - 250);
	shape.setFillColor(sf::Color::White);
	window.draw(shape);

	Name.setFont(myFont);
	Name.setCharacterSize(30);
	Name.setFillColor(sf::Color::Black);
	Name.setPosition(900.f, 500.f);
	
	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode < 128)
		{
			if (event.text.unicode == 13)
			{
				nameGiven = true;
			}
			else if (event.text.unicode == 8)
			{
				if (name.size() > 0)
				{
					name.pop_back();
					Name.setString(name);
				}
				

			}
			else
			{
				name += static_cast<char>(event.text.unicode);
				Name.setString(name);
			}
		}

	}
	
	window.draw(Name);
}

void UI::mainMenu(sf::RenderWindow& window)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(500.f, 500.f));
	shape.setPosition((1920.f / 2) - 250, (1080.f / 2) - 250);
	shape.setFillColor(sf::Color::White);
	window.draw(shape);

	shape.setSize(sf::Vector2f(100.f, 50.f));
	shape.setPosition((1920.f / 2) + 50, (1080.f / 2) - 50);
	shape.setFillColor(sf::Color::Black);
	window.draw(shape);

}

void UI::hotBar(sf::RenderWindow& window, MiniGun& minigun, Weapon& Pistol)
{
	float scale = 1.3f;
	int gridsize = 4;
	sf::Sprite tile;
	tile.setTexture(inventoryslot);
	tile.setTextureRect(sf::IntRect((15 * 64), (13 * 64), 64, 64));
	tile.setScale(scale, scale);

	sf::Sprite minigunsprite;
	minigunsprite.setTexture(weaponInvSprite);

	for (int i = 0; i < 4; i++) {
		tile.setPosition(sf::Vector2f((1920.f / 2.f) - (64 * scale * gridsize / 2) + (i * 64 * scale), (1080.f) - ((64 * scale * gridsize / 2))));
		window.draw(tile);
	}
	if (Pistol.getPickedUp()) 
	{
		minigunsprite.setPosition(sf::Vector2f((1920.f / 2.f) - (64 * scale * gridsize / 2) + (0 * 64 * scale) + ((64 * 1.3f) / 2 - (33 / 2)), (1080.f) - ((64 * scale * gridsize / 2)) + ((64 * 1.3f) / 2 - (33 / 2))));
		minigunsprite.setTextureRect(sf::IntRect(99, 18, 33, 18));
		minigunsprite.setScale(2.f, 2.f);
		window.draw(minigunsprite);
	}
	if (minigun.checkInInventory()) 
	{
		minigunsprite.setPosition(sf::Vector2f((1920.f / 2.f) - (64 * scale * gridsize / 2) + (1 * 64 * scale) + ((64 * 1.3f) / 2 - (33/2)), (1080.f) - ((64 * scale * gridsize / 2)) + ((64 * 1.3f) / 2 - (33/2))));
		minigunsprite.setTextureRect(sf::IntRect(33, 0, 33, 18));
		minigunsprite.setScale(1.3f, 1.3f);
		window.draw(minigunsprite);
	}
	
	
}

void UI::SplashScreen(sf::RenderWindow& window, int colournum)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(500.f, 500.f));
	shape.setPosition((1920.f / 2) - 250, (1080.f / 2) - 250);
	shape.setFillColor(sf::Color::White);
	window.draw(shape);

	shape.setSize(sf::Vector2f(100.f, 100.f));
	shape.setPosition((1920.f / 2) + -50, (1080.f / 2) - 50);
	if(colournum == 0)
		{
		shape.setFillColor(sf::Color::Yellow);
	}
	if (colournum == 1)
	{
		cout << "is red" << endl;
		shape.setFillColor(sf::Color::Red);
	}
	if (colournum == 2)
	{
		shape.setFillColor(sf::Color::Blue);
	}
	if (colournum == 3)
	{
		shape.setFillColor(sf::Color::Cyan);
	}
	window.draw(shape);
}
