#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "SceneManager.h"
#include "Scene.h"

class Engine
{
public:
    Engine(unsigned int width, unsigned int height, const std::string& title);

    void Run();
	sf::RenderWindow& GetWindow();

    static void ChangeScene(std::unique_ptr<Scene> newScene);

private:
    sf::RenderWindow window;
    sf::Clock deltaClock;
};

/*enum class Animation
{
	Up,
	Down,
	Left,
	Right,
	Idle,
};*/

