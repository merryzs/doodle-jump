#pragma once
#include "lib.h"

enum class PowerUpType {
	Papillon,
	Bouclier
};
class PowerUp
{
public:
	PowerUp( sf::Vector2f locs, PowerUpType t);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	sf::FloatRect getBound() const;
	PowerUpType getType() const;
	bool isExpired()const;

	sf::Vector2f getPosition() const;

private:

	sf::RectangleShape buff;
	PowerUpType type;
	sf::Vector2f loc;
	float lifetime;
};

