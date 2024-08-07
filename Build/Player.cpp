#include "Player.h"


void Player::setPlayerSpeed(float newSpeed)
{
	f_playerSpeed = newSpeed;
}

float Player::getPlayerSpeed()
{
	return this->f_playerSpeed;
}

void Player::playerMove(float x, float y)
{
	SetPosition(sf::Vector2f(GetPosition().x + x, GetPosition().y + y));
}

void Player::PlayerInput(Weapon& gun, sf::View* camera, float cameraSpeed, sf::Vector2f mousePos, float dt, int mapsize, int imagesize, MaterialManager& materialmanager, LeaderBoard& leaderboard)
{

	//Check the keyboard for input.
	//moves the camerapov
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (sprite.getPosition().y > (-mapsize * imagesize)) 
		{
			//playerMove(0.f, -cameraSpeed * dt);
			playercamera->move(0.f, -cameraSpeed * dt);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (sprite.getPosition().x > (-mapsize * imagesize)) {
			//playerMove(-cameraSpeed * dt, 0.f);

			playercamera->move(-cameraSpeed * dt, 0.f);
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (sprite.getPosition().y < (mapsize * imagesize)) {
			//playerMove(0.f, cameraSpeed * dt);

			playercamera->move(0.f, cameraSpeed * dt);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (sprite.getPosition().x < (mapsize * imagesize)) {
			//playerMove(cameraSpeed * dt, 0.f);

			playercamera->move(cameraSpeed * dt, 0.f);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		Health = 0;
	}
	
	//reloads the gun
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		gun.reload();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		gun.changeWeapon(1);
		cout << "pistol" << endl;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		gun.changeWeapon(2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
	{
		//materialmanager.printInventory();
		//materialmanager.makeMinigun();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (isFire == false)
		{
			//shoots the gun
			gun.Shoot(window, sprite.getPosition(), MousePos);
			isFire = true;


		}
	}
	else
	{
		isFire = false;
	}
	//sets the rotation of the player, to face the position of the mouse
	//SetRotation(atan2(mousePos.y - window->getSize().y / 2, mousePos.x - window->getSize().x / 2.f) / (3.141 / 180.f));
	//sets the sprite of the player to the position of the centre of the pov, as this moves the camera, not the player
	sprite.setPosition(playercamera->getCenter());

}

//draws the player to the screen
void Player::draw(sf::RenderWindow* window)
{

	sprite.setRotation(GetRotation());
	window->draw(sprite);
}

int Player::gethealth()
{
	return Health;
}

//heals the player, if it has collided with a health pack, and is limited to a health of 100
void Player::getMedkit(bool obtained)
{
	if (obtained == true){
		Health += 40;
		if (Health > 100)
		{
			Health = 100;
		}
	}
}

//checks if the player has collided with the globalbounds of an enemy, if it has, reduce the health, and can only be damaged once per second
void Player::collisions(sf::FloatRect enemy)
{
	if (playerClock.getElapsedTime().asSeconds() >= 1.0f)
	{
		if (sprite.getGlobalBounds().intersects(enemy))
		{
			damagePlayer(10);
			playerClock.restart();
		}
	}
	

}

void Player::damagePlayer(float damage)
{
	Health -= damage;
}

//sets the texture of the player if it has picked up a gun
void Player::setGunTexture()
{

	sprite.setTextureRect(sf::IntRect(0, 0, playerGun.getSize().x, playerGun.getSize().y));

	sprite.setOrigin(sf::Vector2f(playerGun.getSize()) / 2.f);

	sprite.setTexture(playerGun);

}

void Player::restart()
{
	Health = 100;
}

