#pragma once
#include "GameObject.h"
class CraftingMaterial: public GameObject
{
private:
	string typeOfMaterial;
	sf::Color colourMaterial;
	sf::Text text;
	sf::Font myFont;

public:
	bool pickedUp = false;
	int numPickedUp = 0;
	bool craftMiniGum = false;

	string getName();
	sf::Color getColour();
	CraftingMaterial() = default;
	CraftingMaterial(string Name, sf::Color colour) 
	{
		if (!myFont.loadFromFile("../Assets/topdown/Fonts/IHATCS__.TTF"))
		{
			std::cout << "not loading font" << std::endl;
		}
		text.setFont(myFont);
		text.setCharacterSize(30);
		text.setFillColor(sf::Color::Black);

		typeOfMaterial = Name;
		colourMaterial = colour;
	}
	sf::Text draw(sf::Vector2f pos);
};