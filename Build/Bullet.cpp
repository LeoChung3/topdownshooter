#include "Bullet.h"

bool Bullet::getIsFired()
{
	return beingFired;
}

//sets the bullet direction, for when it is fired, so it knows which direction to go when travelling
void Bullet::setBulletDirection(sf::Vector2f Dir)
{
bulletDirection = Dir;
}

//called when the player shoots, set the bool to true, and sets the initial position of where it is to be fired from
void Bullet::fire(sf::Vector2f Pos)
{
	beingFired = true;
	shape.setPosition(Pos);
	position = Pos;

}

//moves the bullet in that direction and will set the bool to false after travelling a set distance, so nothing else can be done with it
void Bullet::move(float dt)
{
	shape.move(bulletDirection * dt);
	sf::Vector2f distance = shape.getPosition() - position;
	float length = std::sqrt((distance.x * distance.x) + (distance.y * distance.y));
	if (length > 600.f) {
		beingFired = false;
	}
}

//draws the bullet to the screen
void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Bullet::checkBoundaries(sf::RenderWindow& window)
{
	if ((shape.getPosition().x < 0 || shape.getPosition().x > window.getSize().x) || 
		(shape.getPosition().y < 0 || shape.getPosition().y > window.getSize().y)) 
	{
		beingFired = false;

	}
}

// checks if the bullet has collided with an enemy
bool Bullet::HitEnemyCheck(sf::Sprite enemy)
{

	if (shape.getGlobalBounds().intersects(enemy.getGlobalBounds()))
	{
		beingFired = false;
		return true;
	}
}

sf::Vector2f Bullet::returnPosition()
{
	return shape.getPosition();
}
