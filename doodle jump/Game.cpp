#include "Game.h"
#include "Platform.h"
#include "PlatformType.h"
#include "lib.h"
#include "CollisionManager.h"

const float screen_width = 1080.f;
const float screen_height = 1080.f;
const int MAX_PLATFORMS = 8;

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


Game::Game() : window(sf::VideoMode({ 1080,1080 }), "Doodle Jump"), backgroundTexture("images/mini_studio_parti_enfer2.png"), background(backgroundTexture)
{
    window.setFramerateLimit(60);


    sf::View view;
    view.setSize({ screen_width, screen_height });
    view.setCenter({ screen_width / 2.f, screen_height / 2.f });
    window.setView(view);


    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
        std::cerr << "Impossible de charger la police\n";

    platforms.clear();

    float spacing = 150.f;
    float startY = screen_height - 50.f; // sol


    for (int i = 0; i < 10; i++)
    {
        spawnPlatform(platforms, startY - i * spacing);
    }

    player.display();

}

void Game::reset()
{
    score = 0;
    gameover = false;

    player = Player();

    platforms.clear();

    float spacing = 150.f;
    float startY = screen_height - 50.f;

    for (int i = 0; i < 10; i++)
    {
        spawnPlatform(platforms, startY - i * spacing);
    }
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

                if (platforms.size() < MAX_PLATFORMS)
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

        
        background.move({ 0, offset });
    }

    player.warp();

    if (player.pose.y > screen_height)
        gameover = true;

    scoreText.setString("Score: " + std::to_string(score));

}

void Game::render()
{
    window.clear();

    window.draw(background);

    for (const auto& platform : platforms)
        platform.draw(window);

    player.draw(window);

    window.draw(scoreText);

    if (gameover)
    {
        sf::Text gameOverText(font);
        gameOverText.setString("GAME OVER\nPress Spacebar to reset\nPress Escape to quit");
        gameOverText.setCharacterSize(40);
        gameOverText.setPosition({ 100,300 });

        window.draw(gameOverText);
    }

    window.display();
}