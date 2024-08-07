#include "CraftingMaterial.h"

string CraftingMaterial::getName()
{
    return typeOfMaterial;
}

sf::Color CraftingMaterial::getColour()
{
    return colourMaterial;
}

sf::Text CraftingMaterial::draw(sf::Vector2f pos)
{
    text.setPosition(pos.x,pos.y);

    string material = typeOfMaterial + ":" + to_string(numPickedUp);
    text.setString(material);
    return text;
}
