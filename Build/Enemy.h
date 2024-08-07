#pragma once
using namespace std;

#include "GameObject.h"
#include "Weapon.h"

class Enemy : public GameObject
{
private:
	float Health = 0;
	float Damage = 0;
	float Speed = 0;

	bool isAlive = false;

	sf::Texture EnemyGun;
	sf::Sprite sprite;

public:
	void setSpritepos(float a, float b);
	void setHealth(float newHealth);
	float getHealth();

	void setDamage(float newDamage);
	float getDamage();

	void setSpeed(float newSpeed);
	float getSpeed();

	void drawEnemy(sf::RenderWindow* window);
	void move(sf::Vector2f playerPos, sf::FloatRect playerRect, float dt);

	void loadTexture();
	void die(sf::Vector2f playerPos, sf::Vector2f windowSize, int mapSize, int imageSize);
	bool checkAlive();
	sf::Vector2f distanceToPlayer(sf::Vector2f playerPos);

	void setAlive();
	sf::Sprite GetSprite();

	void addTexture();

	Enemy(float health, float damage, float speed)
	{
		loadTexture();
		Health = health;
		Damage = damage;
		Speed = speed;

	}

	Enemy() = default;
	~Enemy()
	{
		cout << "Enemy Destroyed" << endl;
	}
};