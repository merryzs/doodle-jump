#pragma once
#include "lib.h"
#include "Player.h"
#include "Platform.h"

class Game
{
private:


    void spawnPlatform(std::vector<Platform>& platforms, float y);
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

    int score;

public:

    Game();

    void run();


};
