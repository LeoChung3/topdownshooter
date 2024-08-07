#pragma once
#include "MaterialManager.h"
#include <map>
class MiniGun
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	bool inInventory = false;
	MaterialManager* matmanager;
	std::multimap<std::string, int> craftingRequirements =

	{ { "metalTube", 2},
	{ "baseGun", 1},
	{ "Welder", 1},
	{ "metalChair", 1},
	{ "drill", 1},
	{ "largeBoreAmmo", 5}};

	bool canCraft = false;
public:
	void craftItem();
	bool checkInInventory();
	MiniGun(MaterialManager* matmanage)

	{
		if (!texture.loadFromFile("../Assets/topdown/PNG/weapon_machine.png")) {
			std::cout << "Error loading the image!" << std::endl;
		}
		sprite.setTexture(texture);
		matmanager = matmanage;
	}
};