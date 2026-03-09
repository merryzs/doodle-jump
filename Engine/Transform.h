#pragma once

#include "Component.h"
#include <SFML/System/Vector2.hpp>

class Transform : public Component
{
public:
	sf::Vector2f position{0.f, 0.f};
	float rotation = 0.f;
	sf::Vector2f scale{ 1.f, 1.f };
	sf::Vector2f size{ 0.f, 0.f };
};
