#pragma once
#include "lib.h"

class Player
{
public:

	Player();

	void updates();
	void draw(sf::RenderWindow& window);
	void display();
	
	sf::RectangleShape hitbox;
	sf::Vector2f getPosition() const { return pose; }

private:


	float speed = 20.f;

	sf::Vector2f pose;

};

