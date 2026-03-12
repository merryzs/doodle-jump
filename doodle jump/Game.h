#pragma once
#include "lib.h"
#include "Player.h"
#include "Platform.h"
#include "CollisionManager.h"

class Game
{
private:


    void spawnPlatform(std::vector<Platform>& platforms, float y, float width , float height);
    void processEvents();
    void update();
    void render();
    void reset();

    sf::RenderWindow window;

    Player player;
    std::vector<Platform> platforms;

    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::Clock clock;

    CollisionManager collisionManager;

    int score;

public:

    Game();

    void run();


};
