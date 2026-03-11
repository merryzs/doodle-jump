#pragma once
#include <memory>
#include "Scene.h"

class SceneManager
{
public:
    static void ChangeScene(std::unique_ptr<Scene> newScene);

    static void Update(float deltaTime);
    static void Render(sf::RenderWindow& window);

    static Scene* GetCurrentScene();

private:
    static std::unique_ptr<Scene> currentScene;
};