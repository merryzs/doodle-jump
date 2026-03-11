#include "SceneManager.h"

std::unique_ptr<Scene> SceneManager::currentScene = nullptr;

void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene)
{
    if (currentScene)
        currentScene->OnUnload();

    currentScene = std::move(newScene);

    if (currentScene)
        currentScene->OnLoad();
}

void SceneManager::Update(float deltaTime)
{
    if (currentScene)
        currentScene->Update(deltaTime);
}

void SceneManager::Render(sf::RenderWindow& window)
{
    if (currentScene)
        currentScene->Render(window);
}

Scene* SceneManager::GetCurrentScene()
{
    return currentScene.get();
}
