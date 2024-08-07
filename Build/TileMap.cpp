#include "TileMap.h"

int TileMap::getTile()
{
    return 0;
}

//goes through the vector of what the map size is by map size, and sets an image texture to each tile sprite, scaling them, and then drawing them to the screen
//but will only draw the tile if it is intersecting the pov of the player, so it wont draw if its not in view
void TileMap::drawMap(sf::RenderWindow* window, sf::View* camera)
{

    for (int i = -mapSize; i < mapSize; i++)
    {
        for (int i2 = -mapSize; i2 < mapSize; i2++)
        {
            sf::FloatRect currentViewRect(camera->getCenter() - camera->getSize() / 2.f, camera->getSize());

            sf::IntRect Image(imageSize * map[i + mapSize][i2 + mapSize], 0, imageSize, imageSize);
            sf::Sprite tile(SpriteSheet, Image);

            tile.scale(scaling, scaling);
            tile.setPosition(float(i) * imageSize * scaling, float(i2) * imageSize * scaling);

            if (tile.getGlobalBounds().intersects(currentViewRect)) // draws tile only if its within the current playerview
            {
                window->draw(tile);
            }
            
        }
    }
}

//returns map size
int TileMap::getMapSize()
{
    return mapSize;
}

//returns size of image
int TileMap::getImageSize()
{
    return imageSize;
}


