#pragma once
#include "lib.h"
#include "Player.h"
#include "Platform.h"
#include "ColisionManager.h"

class Game
{
private:

    sf::RenderWindow window;

    Player player;
    std::vector<Platform> platforms;

    sf::Texture backgroundTexture;
    sf::Sprite background;

    CollisionManager collisionManager;

    sf::Clock clock;

    int score;

public:

    Game();

    void run();

private:

    void spawnPlatform(std::vector<Platform>& platforms, float y);
    void processEvents();
    void update();
    void render();
    void reset();
};
