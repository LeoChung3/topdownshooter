#include "GameObject.h"

void GameObject::setSpritePos(sf::Vector2f newposition)
{
	sprite.setPosition(newposition);
}

void GameObject::SetPosition(sf::Vector2f newposition)
{
	position = newposition;
}

sf::Vector2f GameObject::GetPosition()
{
	return position;
}

void GameObject::SetRotation(float newRotation)
{
	rotation = newRotation;
}

float GameObject::GetRotation()
{
	return rotation;
}

void GameObject::SetScale(float NewScale)
{
	scale = NewScale;
	sprite.setScale(NewScale, NewScale);
}

float GameObject::GetScale()
{
	return scale;
}

void GameObject::setTexture(sf::Texture newtexture)
{
	texture = newtexture;
	sprite.setTexture(texture);
}

sf::Sprite GameObject::getSprite()
{
	return sprite;
}

void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
