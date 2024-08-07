#pragma once

#include "CraftingMaterial.h"

class MaterialManager
{
private:
	CraftingMaterial metalTube{ "metalTube", sf::Color::Red};
	CraftingMaterial baseGun{ "baseGun", sf::Color::Green };
	CraftingMaterial Welder{ "Welder", sf::Color::Blue };
	CraftingMaterial metalChair{"metalChair", sf::Color::Cyan };
	CraftingMaterial drill{ "drill", sf::Color::Yellow };
	CraftingMaterial largeBoreAmmo{"largeBoreAmmo", sf::Color::White };
	std::vector<CraftingMaterial> worldMaterials;
	std::vector<CraftingMaterial> Inventory;
	std::vector<CraftingMaterial> materialTypes{metalTube,
												baseGun, 
												Welder, 
												metalChair, 
												drill, 
												largeBoreAmmo };
	CraftingMaterial a;



public:

	MaterialManager() = default;
	MaterialManager(int mapsize, int imagesize) 
	{

		int mappixels = mapsize * imagesize;
		/*for (int i = 0; i < 2; i++) {
			worldMaterials.push_back(metalTube);
		}
		worldMaterials.push_back(baseGun);
		worldMaterials.push_back(Welder);
		worldMaterials.push_back(metalChair);
		worldMaterials.push_back(drill);*/
		for (int i = 0; i < 5; i++)
		{ 
			worldMaterials.push_back(metalTube);
			worldMaterials.push_back(baseGun);
			worldMaterials.push_back(Welder);
			worldMaterials.push_back(metalChair);
			worldMaterials.push_back(drill);
			worldMaterials.push_back(largeBoreAmmo);}

			
			
		for (int i = 0; i < worldMaterials.size(); i++) 
		{
			worldMaterials[i].SetPosition(sf::Vector2f((rand() % (mappixels * 2)) - mappixels, (rand() % (mappixels * 2)) - mappixels));
		}
	}

	void draw(sf::RenderWindow& window);
	void Collision(sf::FloatRect playerPos);
	void printInventory(sf::RenderWindow& window, sf::Vector2f mousePos);
	void makeMinigun();
	std::vector<CraftingMaterial> returnMaterials();
	std::vector<CraftingMaterial> returnInventory();
	void MiniGunEnough(int number);
	void MinigunNotEnough(int number);
	void removeMaterials(int number, int ammount);
	void cheat();
	void setMaterialPosition(int number, sf::Vector2f position);
};
