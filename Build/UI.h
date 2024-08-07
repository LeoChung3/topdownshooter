#pragma once
#include "GameObject.h"
#include "MaterialManager.h"
#include "MiniGun.h"
#include "Weapon.h"
#include <sstream>

class UI
{
private:
    sf::Text Health;
    sf::Text Ammo;
    sf::Text KillCount;
    sf::Text Name;
    sf::Font myFont;

    sf::Texture inventoryslot;
    sf::Texture weaponInvSprite;
    std::stringstream ss;
public:
    std::string name;
    bool nameGiven = false;
    UI() 
    {
        //C:/Users/P2712929/source/repos/assignment-1-polymorphism-lennybro123/Assets/topdown/Fonts/ARCADECLASSIC.TTF

        if (!myFont.loadFromFile("../Assets/topdown/Fonts/IHATCS__.TTF"))
        {
            std::cout << "not loading font" << std::endl;
        }
        if (!inventoryslot.loadFromFile("../Assets/topdown/Tilesheet/tilesheet_complete.png"))
        {
            cout << "cant load sprite sheet" << endl;
        }
        if (!weaponInvSprite.loadFromFile("../Assets/topdown/PNG/UK.png"))
        {
            cout << "cant load sprite sheet" << endl;
        }

        Health.setFont(myFont);
        Health.setCharacterSize(30);
        Health.setFillColor(sf::Color::White);
        Health.setPosition(50.f, 0.f);



        Ammo.setFont(myFont);
        Ammo.setCharacterSize(30);
        Ammo.setFillColor(sf::Color::White);
        Ammo.setPosition(50.f, 30.f);

        KillCount.setFont(myFont);
        KillCount.setCharacterSize(30);
        KillCount.setFillColor(sf::Color::White);
        KillCount.setPosition(50.f, 60.f);



    }
    void setHealthText(int health);
    void setAmmoText(int ammo, int magazinesize);
    void setKillText(int kills);
    void draw(sf::RenderWindow&);
    void drawInventory(sf::RenderWindow&, MaterialManager&, sf::Vector2f mousePos, MiniGun&);
    void deathScreen(sf::RenderWindow&, sf::Event);
    void mainMenu(sf::RenderWindow&);
    void hotBar(sf::RenderWindow&, MiniGun&, Weapon&);
    void SplashScreen(sf::RenderWindow&, int colournum);
};