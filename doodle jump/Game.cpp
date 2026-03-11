#include "Game.h"
#include <random>

static std::mt19937 rng(std::random_device{}());
static std::uniform_int_distribution<int> sideDist(0, 1);
const float screen_width = 500.f;
const float screen_height = 700.f;


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


void Game::spawnPlatform(std::vector<Platform>& platforms, float y)
{
    float width = 68.f;
    float height = 14.f;
    
    float x = randomPlatformX(width);
    platforms.emplace_back(sf::Vector2f(x, y), sf::Vector2f(width, height));

    for (size_t i = 0; i < platforms.size();)
    {
        if (platforms[i].getPosition().y > screen_height)
        {
            platforms.erase(platforms.begin() + i);
            spawnPlatform(platforms, -10.f);
        }
        else
        {
            ++i;
        }
    }

}


Game::Game() : window(sf::VideoMode({ 500,700 }), "Doodle Jump"), backgroundTexture("images/background.png"), background(backgroundTexture)
{
    window.setFramerateLimit(60);


    sf::View view;
    view.setSize({ screen_width, screen_height });
    view.setCenter({ screen_width / 2.f, screen_height / 2.f });
    window.setView(view);


    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
        std::cerr << "Impossible de charger la police\n";


    float spacing = 150.f;
    float startY = screen_height - 50.f; // sol
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
}

void Game::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        player.moveLeft();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        player.moveRight();

    player.update();

    for (auto&platform: platforms)   
    {            
        if (player.checkCollisions(platform)) player.jump();
    }

    const float scrollLimit = 150.f;

    if (player.getY() < scrollLimit)
    {
        float offset = scrollLimit - player.getY();
        player.setY(scrollLimit);
        for (auto& platform : platforms)
        {
            platform.move({ 0.f, offset });
        }
    }

    for (size_t i = 0; i < platforms.size(); ++i)
    {
        if (platforms[i].getPosition().y > screen_height)
        {
            platforms.erase(platforms.begin() + i);
            spawnPlatform(platforms, -14.f);
        }
    }
}

void Game::render()
{
    window.clear();

    window.draw(background);

    for (auto& p : platforms)
        p.draw(window);

    player.draw(window);

    window.display();
}