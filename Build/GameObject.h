#pragma once
#include "Initialise.h"
using namespace std;

class GameObject
{
protected:
	sf::Vector2f position;

	sf::Vector2f size;

	float rotation = 0.f;
	float scale = 0.f;

	sf::Texture texture;
	sf::Sprite sprite;

public:
	void setSpritePos(sf::Vector2f newposition);
	void SetPosition(sf::Vector2f newposition);
	sf::Vector2f GetPosition();
	void SetRotation(float newRotation);
	float GetRotation();
	void SetScale(float NewScale);
	float GetScale();

	void setTexture(sf::Texture newtexture);
	sf::Sprite getSprite();

	void draw(sf::RenderWindow&);
	GameObject() = default;
	~GameObject()
	{
		cout << "GameObject Destroyed" << endl;
	};
};