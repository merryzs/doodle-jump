#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <filesystem>
#include "Direction.h"
#include "Scene.h"

class GameObject;

class Component
{
public:

	virtual ~Component() = default;

	virtual void Start() {};
	virtual void Update(float delta_time) {};
	virtual void Render(sf::RenderWindow& window) {};
	virtual void Destroy() {};

	GameObject* GetOwner() const
	{
		return owner;
	}

	void SetOwner(GameObject* newOwner)
	{
		owner = newOwner;
	};

protected:
	GameObject* owner = nullptr;
};
