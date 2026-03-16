#pragma once
#include "lib.h"
#include "Player.h"
#include "Platform.h"
#include "CollisionManager.h"
#include "Wave.h"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void reset();
    void spawnPlatform(std::vector<Platform>& platforms, float y, float width = 120.f, float height = 20.f);

private:
    sf::RenderWindow window;

    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::Font font;
    sf::Text scoreText;

    Player player;
    std::vector<Platform> platforms;
    CollisionManager collisionManager;

    sf::Texture waveTexture;
    std::optional<Wave> wave;

    int score = 0;
    bool gameover = false;

    sf::Clock clock;
};