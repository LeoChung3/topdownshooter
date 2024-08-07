#include "MaterialManager.h"

void MaterialManager::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < worldMaterials.size(); i++)
	{
		if (!worldMaterials[i].pickedUp)
		{

			sf::RectangleShape shape;
			shape.setSize(sf::Vector2f(50.f, 50.f));
			shape.setPosition(worldMaterials[i].GetPosition());
			shape.setFillColor(worldMaterials[i].getColour());
			//window.draw(metalTube[i].getSprite());
			window.draw(shape);

		}
	}
	
}

void MaterialManager::printInventory(sf::RenderWindow& window,sf::Vector2f mousePos)
{
	//this will display the ammount of materials to the console, but it is not needed
	/*cout << "=================================" << endl;
	cout << "metalTube: " + to_string(metalTube.numPickedUp) << endl;
	cout << "baseGun: " + to_string(baseGun.numPickedUp) << endl;
	cout << "Welder: " + to_string(Welder.numPickedUp) << endl;
	cout << "metalChair: " + to_string(metalChair.numPickedUp) << endl;
	cout << "drill:" + to_string(drill.numPickedUp) << endl;
	cout << "largeBoreAmmo:" + to_string(largeBoreAmmo.numPickedUp) << endl;
	cout << "=================================" << endl;*/

	//17 x 12
	for (int i = 0; i < materialTypes.size(); i++)
	{
		window.draw(materialTypes[i].draw(sf::Vector2f((1920.f / 2.f) + (64 * 1.3f * 2), (1080.f / 2.f) - ((64 * 1.3 * 4 / 2) - (i * 30.f)))));

	}
}

void MaterialManager::makeMinigun()
{
	if (metalTube.numPickedUp >= 2) {
		metalTube.craftMiniGum = true;
	}
	if (baseGun.numPickedUp >= 1) {
		baseGun.craftMiniGum = true;
	}
	if (Welder.numPickedUp >= 1) {
		Welder.craftMiniGum = true;
	}
	if (metalChair.numPickedUp >= 1) {
		metalChair.craftMiniGum = true;
	}
	if (drill.numPickedUp >= 1) {
		drill.craftMiniGum = true;
	}
	if (largeBoreAmmo.numPickedUp >= 5) {
		largeBoreAmmo.craftMiniGum = true;
	}

	if (largeBoreAmmo.craftMiniGum && drill.craftMiniGum && metalChair.craftMiniGum && Welder.craftMiniGum && baseGun.craftMiniGum && metalTube.craftMiniGum)
	{
		cout << "mini gun craftable" << endl;
	}
	else {
		cout << "mini gun not craftable" << endl;
	}

}

std::vector<CraftingMaterial> MaterialManager::returnMaterials()
{
	return materialTypes;
}

std::vector<CraftingMaterial> MaterialManager::returnInventory()
{
	return Inventory;
}

void MaterialManager::MiniGunEnough(int number)
{
	materialTypes[number].craftMiniGum = true;
}

void MaterialManager::MinigunNotEnough(int number)
{
	materialTypes[number].craftMiniGum = false;

}

void MaterialManager::removeMaterials(int number, int ammount)
{
	materialTypes[number].numPickedUp -= ammount;

}

void MaterialManager::cheat()
{
	for (int a = 0; a < materialTypes.size(); a++) 		{
			materialTypes[a].numPickedUp += 10;
		}
	
}

void MaterialManager::setMaterialPosition(int number, sf::Vector2f position)
{
	worldMaterials[number].SetPosition(position);
}

void MaterialManager::Collision(sf::FloatRect playerPos)
{
	for (int i = 0; i < worldMaterials.size(); i++) {
		if (!worldMaterials[i].pickedUp) 
		{

			sf::Sprite item;
			sf::RectangleShape shape;
			item.setPosition(worldMaterials[i].GetPosition());
			item.setTextureRect(sf::IntRect(0, 0, 50, 50));
			if (item.getGlobalBounds().intersects(sf::FloatRect(playerPos)))
			{

				worldMaterials[i].pickedUp = true;
				Inventory.push_back(worldMaterials[i]);
				for (int a = 0; a < materialTypes.size(); a++) {
					if (worldMaterials[i].getName() == materialTypes[a].getName())
					{
						materialTypes[a].numPickedUp += 1;
					}
				}
			}
		}
	}
}


