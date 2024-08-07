#include "EnemyManager.h"

//goes theough the list of enemies, and calls the move function of each one
void EnemyManager::move(sf::Vector2f playerPos, sf::FloatRect playerRect, float dt)
{
    for (int i = 0; i < NumOfEnemies; i++) {
        Enemies[i].move(playerPos, playerRect, dt);
    }
}

//goes through the list of ememies, and calls each of their draw class, to draw to the screen if it is alive
void EnemyManager::draw(sf::RenderWindow* window)
{
    for (int i = 0; i < NumOfEnemies; i++) {
        if (Enemies[i].checkAlive() == true) {
            Enemies[i].loadTexture();
            Enemies[i].drawEnemy(window);
        }
    }




}

//returns the whole class of the specific enemy in the list
Enemy EnemyManager::returnEnemyNum(int i)
{
    return Enemies[i];
}

//returns the number of enemies
int EnemyManager::getNumOfEnemies()
{
    return NumOfEnemies;
}

//returns the sprite of ths specific position in the list
sf::Sprite EnemyManager::getSprite(int a)
{
    return Enemies[a].GetSprite();
}

//when the enemy is killed, this is called, calling the die class which will give it a new position on the map
void EnemyManager::KillEnemy(int a, bool killed, sf::Vector2f playerPos, sf::Vector2f windowSize, int mapSize, int imageSize)
{
    if (killed == true) {
        Enemies[a].die( playerPos,  windowSize,  mapSize,  imageSize);
        Killed += 1;
    }
}

//returns the ammount of kills the player has
int EnemyManager::getKills()
{
    return Killed;
}

void EnemyManager::restart()
{
    Killed = 0;
}

