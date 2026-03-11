#include "Engine.h"

Engine::Engine(unsigned int width, unsigned int height, const std::string & title)
    : window(sf::VideoMode({ width, height }), title)
{
}

sf::RenderWindow& Engine::GetWindow()
{
    return window;
}

void Engine::Run()
{
    while (window.isOpen())
    {
        // Calcul du deltaTime
        float deltaTime = deltaClock.restart().asSeconds();

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Mise à jour de la scène active
        SceneManager::Update(deltaTime);

        // Rendu
        window.clear();
        SceneManager::Render(window);
        window.display();
    }
}

void Engine::ChangeScene(std::unique_ptr<Scene> newScene)
{
    SceneManager::ChangeScene(std::move(newScene));
}

