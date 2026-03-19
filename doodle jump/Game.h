#pragma once
#include "lib.h"
#include "Player.h"
#include "Platform.h"
#include "CollisionManager.h"
#include "Wave.h"
#include "GameState.h"
#include "MainMenu.h"
#include "Menu.h"
#include "Defeat.h"
#include "WinMenu.h"
#include "Enemy.h"
#include "PlatformType.h"
#include "Random.h"

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

    std::vector<std::unique_ptr<Enemy>> enemies;

    const int SCORE_SPAWN_ENEMY = 1000;
    int lastEnemyScore = 0;

    void spawnEnemy(float y, EnemyType type);
    void checkEnemyCollisions();


    sf::Texture waveTexture;

    std::unique_ptr<Wave> wave;
    bool waveActive = false;
    int nextWaveScore = 1500;
    int waveScoreGap = 1500;




    int score = 0;

    sf::Clock clock;
};