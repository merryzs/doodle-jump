#include "Scene.h"
#include "Component.h"
#include "GameObject.h"
#include "Times.h"

void Scene::Start()
{
	GameObject* player = new GameObject();
	player->Start();

	gameObjects.push_back(player);

	for (GameObject* obj : gameObjects)
		obj->Start();
}

void Scene::AddGameObject(GameObject* obj) 
{
	gameObjects.push_back(obj);
}

void Scene::Update(float deltaTime)
{
	Times::Update();
	float dt = Times::DeltaTime();

	for (GameObject* obj : gameObjects)
		obj->Update(dt);
}

void Scene::Render(sf::RenderWindow& window)
{
	for (GameObject* obj : gameObjects)
		obj->Render(window);

}

void Scene::Destroy() 
{
	for (GameObject* obj : gameObjects)
		obj->Destroy();
}
