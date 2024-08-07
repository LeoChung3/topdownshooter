#include "Weapon.h"
#include <thread>

//goes through all the bullets and moves them if they have been fired
void Weapon::move(sf::RenderWindow& window, float dt)
{

	for (int i = 0; i <= maxBullets; i++)
	{
		if (bullets[i].getIsFired() == true) {
			bullets[i].move(dt);

		}
	}
}

//draws the bullets if they have been fired, and checks if the gun has been picked up, if not, draw the gun to the screen
void Weapon::draw(sf::RenderWindow& window)
{
	for (int i = 0; i <= maxBullets; i++)
	{
		if (bullets[i].getIsFired() == true) {
			bullets[i].draw(window);
		}
	}
	if (pickedup == false) {
		window.draw(gunSprite);
	}
}

//find the velocity of the bullet it should travel, which is the direction of the player to the mouse
//then sets the velocity and fires it
//and removes one from the magazine
void Weapon::Shoot(sf::RenderWindow* window, sf::Vector2f playerPos, sf::Vector2f mousepos)
{
	sf::Vector2f distance = sf::Vector2f(mousepos.x - window->getSize().x/2, mousepos.y - window->getSize().y/2);
	float length = std::sqrt((distance.x * distance.x) + (distance.y * distance.y));
	distance /= length;

	sf::Vector2f vel = distance * bulletSpeed;
	if (pickedup == true)
	{
		for (int i = 0; i <= maxBullets; i++) 
		{
			if (bullets[i].getIsFired() == false && magazine > 0) 
			{
				bullets[i].setBulletDirection(vel);
				bullets[i].fire(playerPos);
				magazine -= 1;
				break;
			}
			else 
			{
			}
		}
	}
}

//returns magazine
int Weapon::returnMagazine()
{
	return magazine;
}

int Weapon::returnmagazinesize()
{
	return maxBullets;
}

//reloads magazine, setting the variable back to 10
void Weapon::reload()
{
	magazine = maxBullets;
}

//checks if the gun was picked up by the player, if it is, the bool is set to true so it can be used by other functions
void Weapon::pickup(sf::FloatRect player)
{
	if (gunSprite.getGlobalBounds().intersects(player)) 
	{
		pickedup = true;
	}
}

//returns if gun is picked up
bool Weapon::getPickedUp()
{
	return pickedup;
}

void Weapon::printbullet(int i)
{
	cout << bullets[i].returnPosition().x << bullets[i].returnPosition().y << endl;
}


//goes through the list of bullets, checking if they have collided with an enemy
bool Weapon::guncollisions(sf::Sprite enemy)
{
	for (int i = 0; i <= maxBullets; i++)
	{
		if (bullets[i].getIsFired() == true)
		{
			if (bullets[i].HitEnemyCheck(enemy) == true) {
				return true;
			}

		}
		else {
			return false;
		}
	}
}

void Weapon::changeWeapon(int number)
{
	switch (number)
	{
	case (1):
		if (pickedup)
		{
			magazine = 10;
			maxBullets = 10;
			bulletSpeed = 10;
			break;
		}

	case(2):
		if (minigunweapon->checkInInventory())
		{
			magazine = 30;
			maxBullets = 30;
			bulletSpeed = 30;
		}
		break;
	}
}

void Weapon::setFired(int i ,sf::Vector2f pos)
{
	bullets[i].fire(pos);
}

