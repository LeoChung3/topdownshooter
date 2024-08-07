#pragma once
#include "Initialise.h"
class Bullet
{
private:
	sf::CircleShape shape;

	sf::Vector2f position;
	sf::Vector2f bulletDirection;
	bool beingFired = false;

	float speed = 5.f;
	


public:
	bool getIsFired();
	void setBulletDirection(sf::Vector2f Dir);
	void fire(sf::Vector2f Pos);
	void move(float dt);
	void draw(sf::RenderWindow&);
	void checkBoundaries(sf::RenderWindow&);
	bool HitEnemyCheck(sf::Sprite enemy);
	sf::Vector2f returnPosition();
	Bullet() 
	{
		shape.setRadius(10.f);
		shape.setFillColor(sf::Color::Green);
	}
};