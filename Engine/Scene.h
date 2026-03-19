#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class GameObject;

class Scene
{
public:
	
	void Start();
	void AddGameObject(GameObject* obj);
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;
	void Destroy();

	virtual ~Scene() = default;

	virtual void OnLoad() {}
	virtual void OnUnload() {}

private:	

	std::vector<GameObject*> gameObjects;
	
};
