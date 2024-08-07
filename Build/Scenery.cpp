#include "Scenery.h"

//goes through the lst of positions set, and draws the scenery to that position
void Scenery::drawScenery(float mapsize, float imagesize, sf::RenderWindow& window)
{
	sf::IntRect Image(imagesize * 20, imagesize * 6, imagesize, imagesize);

	for (int i = 0; i < 10; i++)
	{
		sf::Sprite tree(SpriteSheet, Image);

		tree.setPosition(treePos[i]);

		window.draw(tree);
	}

}
