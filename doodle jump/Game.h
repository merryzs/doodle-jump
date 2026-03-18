#pragma once
#include "lib.h"
#include "Player.h"
#include "Enemy.h"
#include "Platform.h"
#include "PowerUp.h"
#include "CollisionManager.h"

class Game
{
private:


    void spawnPlatform(std::vector<Platform>& platforms, float y, float width = 225.f, float height = 10.f);
    void processEvents();
    void update();
    void render();
    void reset();

    sf::RenderWindow window;

    Player player;
    std::vector<std::unique_ptr<Enemy>> enemies;

    const int SCORE_SPAWN_ENEMY = 1000;
    int lastEnemyScore = 0;

    void spawnEnemy(float y, EnemyType type);
    void checkEnemyCollisions();
    void spawnPowerUpOnPlatform(const Platform& platform);

    std::vector<Platform> platforms;
    std::vector<std::unique_ptr<PowerUp>> powerUps;

    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::Font font;
    sf::Text scoreText;

    int score = 0;
    bool gameover = false;

    sf::Clock clock;

    CollisionManager collisionManager;

public:

    Game();

    void run();


};
