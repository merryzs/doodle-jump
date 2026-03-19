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
    void spawnWave();

private:
    sf::RenderWindow window;

    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::Font font;
    sf::Text scoreText;

    Player player;
    std::vector<Platform> platforms;
    CollisionManager collisionManager;

    

    std::unique_ptr<Wave> wave;
    sf::Texture waveTexture;
    bool waveActive = false;   
    int nextWaveScore = 1500;   
    int waveScoreGap = 1500;

    int score = 0;
    bool gameover = false;

    sf::Clock clock;
};