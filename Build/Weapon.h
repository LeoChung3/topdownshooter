#pragma once

#include "Bullet.h"
#include "Enemy.h"
#include "MiniGun.h"
class Weapon
{
private:
	sf::Texture gunTexture;
	sf::Sprite gunSprite;
	sf::Vector2f Direction;
	MiniGun* minigunweapon;
	Bullet bullets[30];
	int magazine;
	int maxBullets;
	float bulletSpeed;
	bool pickedup = false;
	enum weapontype
	{
		Pistol = 1,
		minigun = 2
	};
public:
	void move(sf::RenderWindow&, float dt);
	void draw(sf::RenderWindow&);
	void Shoot(sf::RenderWindow*, sf::Vector2f playerPos, sf::Vector2f mousepos);
	int returnMagazine();
	int returnmagazinesize();
	void reload();
	void pickup(sf::FloatRect player);
	bool getPickedUp();

	void printbullet(int i);
	bool guncollisions(sf::Sprite enemy);

	void changeWeapon(int number);

	void setFired(int i, sf::Vector2f pos);
	Weapon(int a, float b, MiniGun* c)
	{
		magazine = a;
		maxBullets = a;
		bulletSpeed = b;
		minigunweapon = c;
		if (!gunTexture.loadFromFile("../Assets/topdown/PNG/weapon_gun.png")) {
			std::cout << "Error loading the image!" << std::endl;
		}
		gunSprite.setTexture(gunTexture);
		gunSprite.setPosition(0.f, -300.f);
	}

	Weapon()
	{
		magazine = 20;
		maxBullets = 20;
		bulletSpeed = 25.f;
		if (!gunTexture.loadFromFile("../Assets/topdown/PNG/weapon_gun.png")) {
			std::cout << "Error loading the image!" << std::endl;
		}
		gunSprite.setTexture(gunTexture);
		gunSprite.setPosition(0.f, -300.f);
	}


};