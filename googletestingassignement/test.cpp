#include "pch.h"
#include "../Build/GameObject.h"
#include "../Build/GameObject.cpp"
#include "../Build/Enemy.h"
#include "../Build/Enemy.cpp"
#include "../Build/MiniGun.h"
#include "../Build/MiniGun.cpp"
#include "../Build/Weapon.h"
#include "../Build/Weapon.cpp"
#include "../Build/bullet.h"
#include "../Build/bullet.cpp"
#include "../Build/MaterialManager.h"
#include "../Build/MaterialManager.cpp"
#include "../Build/CraftingMaterial.h"
#include "../Build/CraftingMaterial.cpp"
#include "../Build/LeaderBoard.h"
#include "../Build/LeaderBoard.cpp"
#include "../Build/Player.h"
#include "../Build/Player.cpp"
#include "../Build/Potion.h"
#include "../Build/Potion.cpp"
#include "../Build/Collectable.h"
#include "../Build/Collectable.cpp"


class GameTests : public testing::Test {
protected:
    static void SetUpTestSuite() 
    {
    }

    static void TearDownTestSuite() 
    {
    }

public:
    sf::RenderWindow window;
    Player player;


    GameTests() = default;
    ~GameTests() override = default;
    void SetUp() override {
        window.create(sf::VideoMode(1920, 1080, 32), "Game Demo", sf::Style::Default);
    }

    void TearDown() override {
    }
};

TEST_F(GameTests, TestingOriginalPlayerHealth) {
    ASSERT_EQ(player.gethealth(), 100); // checks if the initiated player health is equal to 100
}

TEST_F(GameTests, getHealthkit) {
    player.damagePlayer(10); // damages the player by 10 points
    EXPECT_NE(player.gethealth(), 100); // checks if the player health is not equal to 100
    player.getMedkit(true);// heals the player health
    EXPECT_EQ(player.gethealth(), 100); // player should be at max health

}


//1. Test the correctness of the movement of the character across a suitable spread of values.
//done 
TEST(Playertesting, testplayermovement) {
    Player player;
    sf::Vector2f originalPos = player.GetPosition(); // gets original player pos
    player.playerMove(100.f, 0.f); // moves the player
    EXPECT_NE(player.GetPosition(), originalPos);
    EXPECT_EQ(player.GetPosition().x, originalPos.x + 100.f);
    EXPECT_LT(player.GetPosition().y, 1); // checks so that the y position was not changed at all, so it only went straight down
    EXPECT_GT(player.GetPosition().y, -1);

    player.playerMove(100.f, -100.f);
    EXPECT_EQ(player.GetPosition(), sf::Vector2f(200.f, -100.f));

    player.playerMove(0.f, -100.f);
    EXPECT_EQ(player.GetPosition(), sf::Vector2f(200.f, -200.f));
}

//3. Test whether the position of a character is calculated correctly in relation to at least 3 gameobjects.
TEST(ObjectTesting, distanceofobjectstoplayer)
{

    Player player;
    player.playerMove(100.f, 0.f);
    Enemy enemy;
    enemy.setSpritepos(0.f, 0.f);
    EXPECT_EQ(enemy.distanceToPlayer(player.GetPosition()), sf::Vector2f(100.f, 0.f)); // checks the distance of the enemy in relation to the player

    player.playerMove(100.f, 0.f);
    Enemy enemy2;
    enemy2.setSpritepos(300, 300);
    EXPECT_EQ(enemy2.distanceToPlayer(player.GetPosition()), sf::Vector2f(-100.f, -300.f)); // checks the distance of the enemy in relation to the player

}
//4. Test the correctness of a collision function across a suitable spread of values / objects.
TEST(Collisiontest, collisiontesting) {

    Enemy enemy;
    enemy.loadTexture();
    Weapon gun;
    gun.setFired(0, sf::Vector2f(0, 0));
    EXPECT_TRUE(gun.guncollisions(enemy.GetSprite())); // checks the collision between a bullet and the enemy

    Player player;
    Collectable collectables(20, 64, 7);
    collectables.setPos(0, sf::Vector2f(0.f, 0.f));
    EXPECT_TRUE(collectables.collided(player.getSprite()));

}

//5. Test whether a specific collectable is in the inventory and that its position in the inventory is correct, 
//for example test the position of a weapon, check its accessibility is correct, and it is where it is expected
//in the container used.
TEST(InventoryTest, MaterialsCount)
{

    Player player(100, 0.f, 1.f, 5.f);
    player.setSpritePos(sf::Vector2f(25.f, 25.f));
    MaterialManager matmanager(20, 64);
    matmanager.setMaterialPosition(0, sf::Vector2f(0.f, 0.f));
    matmanager.Collision(player.getSprite().getGlobalBounds());
    matmanager.setMaterialPosition(1, sf::Vector2f(0.f, 0.f));
    matmanager.Collision(player.getSprite().getGlobalBounds());

    EXPECT_EQ(matmanager.returnInventory()[0].getName(), "metalTube");
    EXPECT_STRNE(matmanager.returnInventory()[0].getName().c_str(), "metaltube");

    EXPECT_EQ(matmanager.returnInventory()[1].getName(), "baseGun");
    EXPECT_STRNE(matmanager.returnInventory()[1].getName().c_str(), "BASEGUN"); // shows that the string comparisons, that the names have to in camel case for the tests to work

}

//6. Test whether a sprite or texture of a sprite can be loaded.
TEST(PlayerTest, PlayerTexure)
{
    Player player;
    ASSERT_FALSE(player.getSprite().getTexture());
    Player player2(100, 0.f, 1.f, 5.f);
    ASSERT_TRUE(player2.getSprite().getTexture()); // shows that the texture can only be loaded when a player is passed in with data, which the game would only work if it is.


}
//7. Test the correctness of the sequence of destructor calls, for example
//from weapon to gameobject
TEST(DestructorTest, PotiontocollectableDestructor)
{
    testing::internal::CaptureStdout();

    { 
    Potion healthkit; 
    }
    std::string output = testing::internal::GetCapturedStdout(); // gets the outputting console line from destructors
    EXPECT_EQ(output, "health kit collected\nGameObject Destroyed\n");

    testing::internal::CaptureStdout();
    {
        Enemy enemy;
    }
    std::string output2 = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output2, "Enemy Destroyed\nGameObject Destroyed\n"); // compared the outputted console lines, if the deconstructor is being called correctly, from the derived class up to the base class
}





