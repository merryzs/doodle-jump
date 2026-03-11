#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>
#include "Platform.h"
#include "PlatformType.h"

const float SCREEN_WIDTH = 1200.f;
const float SCREEN_HEIGHT = 1600.f;


float randomPlatformX(float platformWidth)
{
    float halfScreen = SCREEN_WIDTH / 2.f;

    if (sideDist(rng) == 0)
    {
        std::uniform_real_distribution<float> dist(0.f, halfScreen - platformWidth);
        return dist(rng);
    }
    else
    {
        std::uniform_real_distribution<float> dist(halfScreen, SCREEN_WIDTH - platformWidth);
        return dist(rng);
    }
}

void spawnPlatform(std::vector<Platform>& platforms, float y, float width = 225.f, float height = 10.f)
{
    float x = randomPlatformX(width);

    PlatformType type = randomPlatformType();

    platforms.emplace_back(
        sf::Vector2f(x, y),
        sf::Vector2f(width, height),
        type
    );

    
}

int main()
{
    
    sf::RenderWindow window(sf::VideoMode({ (unsigned)SCREEN_WIDTH, (unsigned)SCREEN_HEIGHT }), "Doodle Jump Clone");
    window.setFramerateLimit(60);

   
    sf::View view;
    view.setSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
    view.setCenter({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
    window.setView(view);

    
    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
        std::cerr << "Impossible de charger la police\n";

   
    std::vector<Platform> platforms;

   
    float spacing = 150.f;
    float startY = SCREEN_HEIGHT - 50.f; // sol
    for (int i = 0; i < 10; i++)
    {
        spawnPlatform(platforms, startY - i * spacing);
    }

   
    float playerY = SCREEN_HEIGHT - 100.f;
    float playerVelocityY = 0.f;
    const float gravity = 1200.f;

    
  
    
        
        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }

        
        playerVelocityY += gravity * 1.f / 60.f;
        playerY += playerVelocityY * 1.f / 60.f;

      
        const float CAMERA_LIMIT = SCREEN_HEIGHT / 2.f;
        if (playerY < CAMERA_LIMIT)
        {
            float offset = CAMERA_LIMIT - playerY;
            playerY = CAMERA_LIMIT;

            for (auto& p : platforms)
                p.move({ 0.f, offset });
        }

        
        for (size_t i = 0; i < platforms.size();)
        {
            if (platforms[i].getPosition().y > SCREEN_HEIGHT)
            {
                platforms.erase(platforms.begin() + i);
                spawnPlatform(platforms, -10.f); 
            }
            else
            {
                ++i;
            }
        }

      
        window.clear(sf::Color::Black);

       
        for (const auto& platform : platforms)
            platform.draw(window);

        window.display();
    }

    return 0;
}