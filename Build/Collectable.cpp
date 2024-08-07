#include "Collectable.h"

//checks if the player has collided with the collectable of health item, if it is, the bool is true, so it cant be picked up again
bool Collectable::collided(sf::Sprite player)
{
	/*for (int i = 0; i < healthPickUps; i++) {
		if (Healthkits[i].pickedUp == false) {
			if (Healthkits[i].getSprite().getGlobalBounds().intersects(player.getGlobalBounds())) {
				Healthkits[i].pickedUp = true;
				Healthkits[i].~Potion();
				healthPickUps -= 1;
				return true;
			}
		}
	}*/
	for (std::vector<Potion>::iterator it = Healthkits.begin(); it != Healthkits.end(); it++)
	{
		if (it->pickedUp == false) {
			if (it->getSprite().getGlobalBounds().intersects(player.getGlobalBounds())) {
				it->pickedUp = true;
				it->~Potion();
				Healthkits.erase(it);
				healthPickUps -= 1;
				return true;
			}
		}
	}	
}

//draws all collectables to the screen
void Collectable::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < healthPickUps; i++)
	if (Healthkits[i].pickedUp == false) {
		window.draw(Healthkits[i].getSprite());
	}

}

void Collectable::setPos(int a, sf::Vector2f Pos)
{
	Healthkits[a].setPosition(Pos);
}
