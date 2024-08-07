#include "Enemy.h"

void Enemy::setSpritepos(float a, float b)
{
	sprite.setPosition(a, b);
}

void Enemy::setHealth(float newHealth)
{
	Health = newHealth;
}

float Enemy::getHealth()
{
	return Health;
}

void Enemy::setDamage(float newDamage)
{
	Damage = newDamage;
}

float Enemy::getDamage()
{
	return Damage;
}

void Enemy::setSpeed(float newSpeed)
{
	Speed = newSpeed;
}

float Enemy::getSpeed()
{
	return Speed;
}

//draws the enemy
void Enemy::drawEnemy(sf::RenderWindow* window)
{
	window->draw(sprite);
}


//finds the distance between the enemy and player, created a velocity vector and if it is within a set distance, 
// it moves towards the player, and the rotation is facing the player
void Enemy::move(sf::Vector2f playerPos, sf::FloatRect playerRect, float dt)
{
	sf::Vector2f distance = distanceToPlayer(playerPos);
		float length = std::sqrt((distance.x * distance.x) + (distance.y * distance.y));
		distance /= length;

		sf::Vector2f vel = distance * Speed;
		if (length < 750.f && isAlive && !sprite.getGlobalBounds().intersects(playerRect))
		{	// enemy only moves towards player if within a 500 pixel range and is alive
			sprite.move(vel * dt);
			sprite.setRotation(atan2(playerPos.y - sprite.getPosition().y, playerPos.x - sprite.getPosition().x) / (3.141 / 180));

		}

	
}

//adds a texture to the texture variable
void Enemy::loadTexture()
{
	if (!EnemyGun.loadFromFile("../Assets/topdown/PNG/Robot 1/robot1_gun.png")) {
		std::cout << "Error loading the image!" << std::endl;
	}
	sprite.setTexture(EnemyGun);
}

//moves the enemy to a whole different position if it is called, due to the enemy dying in another function
void Enemy::die(sf::Vector2f playerPos, sf::Vector2f windowSize, int mapSize, int imageSized)
{
	int mappixels = mapSize * imageSized;
	sprite.setPosition((rand() % (mappixels * 2)) - mappixels, (rand() % (mappixels * 2)) - mappixels);
	
}

//returns if the alive bool is alive or not
bool Enemy::checkAlive()
{

	return isAlive;
}

sf::Vector2f Enemy::distanceToPlayer(sf::Vector2f playerPos)
{
	return playerPos - sprite.getPosition();
}

//sets the enemy bool to alive
void Enemy::setAlive()
{
	isAlive = true;
}

//returns the whole enemy sprit
sf::Sprite Enemy::GetSprite()
{
	return sprite;
}


