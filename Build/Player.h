#pragma once

using namespace std;

#include "GameObject.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Enemy.h"
#include "MaterialManager.h"
#include "LeaderBoard.h"

class Player : public GameObject
{
private:
	int Health;
	float f_playerSpeed;
	sf::Texture txt_playerLeft;
	sf::Texture playerGun;

	bool isFire = false;

	sf::Clock playerClock;

	int kills = 0;

public:
	sf::Vector2f MousePos;
	sf::View* playercamera;
	sf::RenderWindow* window;


	void setPlayerSpeed(float newSpeed);
	float getPlayerSpeed();

	void playerMove(float x, float y);
	void PlayerInput(Weapon&, sf::View *camera , float cameraSpeed, sf::Vector2f mousePos, float dt, int mapsize, int imagesize, MaterialManager&, LeaderBoard&);
	void draw(sf::RenderWindow* window);

	int gethealth();
	void getMedkit(bool obtained);

	void collisions(sf::FloatRect);
	void damagePlayer(float damage);
	void setGunTexture();

	void restart();
	Player(int health, float rotation, float scale, float speed)
	{	
		if (!txt_playerLeft.loadFromFile("../Assets/topdown/PNG/Hitman 1/hitman1_hold.png")) {
			std::cout << "Error loading the image!" << std::endl;
		}
		if (!playerGun.loadFromFile("../Assets/topdown/PNG/Hitman 1/hitman1_gun.png")) {
			std::cout << "Error loading the image!" << std::endl;
		}

		sprite.setTextureRect(sf::IntRect(0, 0, txt_playerLeft.getSize().x, txt_playerLeft.getSize().y));
		sprite.setOrigin(sf::Vector2f(txt_playerLeft.getSize()) / 2.f);

		Health = health;
		this->SetRotation(rotation);
		this->SetScale(scale);
		f_playerSpeed = speed;
		sprite.setTexture(txt_playerLeft);
	}
	Player()
	{
		SetPosition(sf::Vector2f(0, 0));
		Health = 100;
		f_playerSpeed = 5;
	}
};
