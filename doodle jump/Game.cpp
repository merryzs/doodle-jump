#include "Game.h"
#include "Platform.h"
#include "PlatformType.h"
#include "lib.h"

const float screen_width = 1080.f;
const float screen_height = 1080.f;

Player player;

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




void Game::spawnPlatform(std::vector<Platform>& platforms, float y, float width = 225.f, float height = 10.f)
{
    float x = randomPlatformX(width);

    PlatformType type = randomPlatformType();

    platforms.emplace_back(
        sf::Vector2f(x, y),
        sf::Vector2f(width, height),
        type
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
                spawnPlatform(platforms, -10.f);
            }
            else
            {
                ++i;
            }
        }



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
    float deltaTime = clock.restart().asSeconds();

    for (auto& p : platforms)
        p.update(deltaTime);

    player.updates(deltaTime);

    player.warp();

}

void Game::render()
{
    window.clear();

    window.draw(background);

    for (const auto& platform : platforms)
        platform.draw(window);

    player.draw(window);

    window.display();
}