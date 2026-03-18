#include "Game.h"
#include "Platform.h"
#include "PlatformType.h"
#include "lib.h"
#include "CollisionManager.h"

const float screen_width = 1080.f;
const float screen_height = 1080.f;
const int max_platforms = 8;

float randomPlatformX(float platformWidth)
{
    float halfScreen = screen_width / 2.f;

    if (sideDist(rng) == 0)
    {
        std::uniform_real_distribution<float> dist(0.f, halfScreen - platformWidth);
        return dist(rng);
    }
    else
    {
        std::uniform_real_distribution<float> dist(halfScreen, screen_width - platformWidth);
        return dist(rng);
    }
}




void Game::spawnPlatform(std::vector<Platform>& platforms, float y, float width, float height)
{
    const int MAX_TRIES = 20;
    const float MIN_VERTICAL_GAP = 100.f;   
    const float MIN_HORIZONTAL_GAP = 100.f; 

    for (int i = 0; i < MAX_TRIES; i++)
    {
        float x = randomPlatformX(width);
        PlatformType type = randomPlatformType();

        Platform newPlat({ x, y }, { width, height }, type);
        sf::FloatRect newBounds = newPlat.getBounds();

        bool overlaps = false;

        for (const auto& p : platforms)
        {
            sf::FloatRect other = p.getBounds();

            
            if (auto inter = newBounds.findIntersection(other))
            {
                if (inter->size.x > 0 && inter->size.y > 0)
                {
                    overlaps = true;
                    break;
                }
            }

            
            if (std::abs(p.getPosition().y - y) < MIN_VERTICAL_GAP)
            {
                overlaps = true;
                break;
            }

           
            if (std::abs(p.getPosition().x - x) < MIN_HORIZONTAL_GAP)
            {
                overlaps = true;
                break;
            }
        }

        if (!overlaps)
        {
            platforms.emplace_back(newPlat);
            return;
        }
    }

    
    platforms.emplace_back(
        sf::Vector2f(randomPlatformX(width), y),
        sf::Vector2f(width, height),
        randomPlatformType()
    );
}

void Game::spawnEnemy(float y, EnemyType type)
{
    float x = static_cast<float>(rand() % 900 + 50);
    enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(x, y), type));
}


Game::Game() : window(sf::VideoMode({ (int)screen_width,(int)screen_height }), "Doodle Jump"), backgroundTexture("images/mini_studio_parti_enfer2.png"), background(backgroundTexture), scoreText(font)
{
    window.setFramerateLimit(60);

    auto size = backgroundTexture.getSize();
    background.setTextureRect(sf::IntRect({ 0, (int)size.y - (int)screen_height }, { (int)screen_width, (int)screen_height }));

    sf::View view;
    view.setSize({ screen_width, screen_height });
    view.setCenter({ screen_width / 2.f, screen_height / 2.f });
    window.setView(view);    

    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
        std::cerr << "Impossible de charger la police\n";

    scoreText.setCharacterSize(32);
    scoreText.setPosition({ 20,20 });
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setString("Score: 0");
    
    platforms.clear();
    enemies.clear();

    float spacing = 150.f;
    float startY = screen_height - 50.f; // sol


    for (int i = 0; i < max_platforms; i++)
    {
        spawnPlatform(platforms, startY - i * spacing);
    }

    player.display();

    score = 0;
    gameover = false;

}

void Game::reset()
{
    score = 0;
    gameover = false;

    player.reset();

    platforms.clear();
    enemies.clear();
    lastEnemyScore = 0;

    float spacing = 150.f;
    float startY = screen_height - 50.f;

    for (int i = 0; i < max_platforms; i++)
    {
        spawnPlatform(platforms, startY - i * spacing);
    }

    auto size = backgroundTexture.getSize();
    background.setTextureRect(sf::IntRect({ 0, (int)size.y - (int)screen_height }, { (int)screen_width, (int)screen_height }));

    scoreText.setString("Score: 0");
}


void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();

        for (size_t i = 0; i < platforms.size();)
        {
            if (platforms[i].getPosition().y > screen_height)
            {
                platforms.erase(platforms.begin() + i);

                if (platforms.size() < max_platforms)
                    spawnPlatform(platforms, -10.f);
            }
            else
            {
                ++i; 
            }
        }

        collisionManager.handle(player, platforms);
        render();
    }
}

void Game::processEvents()
{
    while (auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
    }

    if (gameover && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        reset();

    if (gameover && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        window.close();
}

void Game::update()
{
    float deltaTime = clock.restart().asSeconds();

    for (auto& p : platforms)
        p.update(deltaTime);

    player.updates(deltaTime);

    
    float cameraTriggerY = screen_height * 0.4f;

    if (player.getPose().y < cameraTriggerY)
    {
        float offset = cameraTriggerY - player.getPose().y;
                
        player.setPose({ player.getPose().x, cameraTriggerY });
                
        for (auto& p : platforms)
            p.setPosition({ p.getPosition().x, p.getPosition().y + offset });

        for (auto& e : enemies)
            e->setPosition({ e->getPosition().x, e->getPosition().y + offset });

        sf::IntRect rect = background.getTextureRect();

        rect.position.y -= offset;

        if (rect.position.y < 0)
            rect.position.y = 0;

        background.setTextureRect(rect);

        score += static_cast<int>(offset);
    }

    player.warp();

    if (player.getPose().y > screen_height)
        gameover = true;

    
    if (score - lastEnemyScore >= SCORE_SPAWN_ENEMY)
    {
        lastEnemyScore = score;

        spawnEnemy(-50.f, EnemyType::Static);
        spawnEnemy(-150.f, EnemyType::Moving);
    }

   
    for (auto& enemy : enemies)
    {
        enemy->update(deltaTime);

        
        if (enemy->isActive() && player.getBounds().findIntersection(enemy->getBounds()))
        {
            gameover = true;
        }
    }

    scoreText.setString("Score: " + std::to_string(score));

}

void Game::updateEnemies(float deltaTime)
{
    for (auto& enemy : enemies)
        enemy->update(deltaTime);

    for (size_t i = 0; i < enemies.size(); )
    {
        if (enemies[i]->getPosition().y > screen_height + 100.f)
        {
            enemies.erase(enemies.begin() + i);
        }
        else
        {
            ++i;
        }
    }
}

void Game::checkEnemyCollisions()
{
    sf::FloatRect playerBounds(
        player.hitbox.getPosition(),
        player.hitbox.getSize()
    );

    for (auto& enemy : enemies)
    {
        if (enemy->isActive() && playerBounds.findIntersection(enemy->getBounds()))
        {
            gameover = true;
            return;
        }
    }
}

void Game::render()
{
    window.clear();

    window.draw(background);

    for (const auto& platform : platforms)
        platform.draw(window);

    for (auto& enemy : enemies)
        enemy->draw(window);

    player.draw(window);

    window.draw(scoreText);

    if (gameover)
    {
        sf::RectangleShape gameoverBackground(sf::Vector2f(1080, 1080));
        gameoverBackground.setFillColor(sf::Color::Black);

        sf::Text gameOverText(font);
        gameOverText.setString("GAME OVER");
        gameOverText.setCharacterSize(80);
        gameOverText.setPosition({ 300,300 });
        gameOverText.setFillColor(sf::Color::Red);

        sf::Text resetText(font);
        resetText.setString("Press Spacebar to reset");
        resetText.setCharacterSize(40);
        resetText.setPosition({ 350,600 });
        resetText.setFillColor(sf::Color::Blue);

        sf::Text closeText(font);
        closeText.setString("Press Escape to quit");
        closeText.setCharacterSize(40);
        closeText.setPosition({ 350,800 });
        closeText.setFillColor(sf::Color::Green);
        
        
        window.draw(gameoverBackground);
        window.draw(gameOverText);
        window.draw(resetText);
        window.draw(closeText);
    }

    window.display();
}